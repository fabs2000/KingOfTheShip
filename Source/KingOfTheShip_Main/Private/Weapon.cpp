// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Math/RandomStream.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "ConstructorHelpers.h"
#include "Pirate.h"


UWeapon::UWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> powerShotAsset(
		TEXT("/Game/Blueprints/PowerShotProjectile_BP.PowerShotProjectile_BP_C"));
	if (powerShotAsset.Succeeded())
		m_PowerShot = powerShotAsset.Object;


	//m_pShotSource = CreateDefaultSubobject<UArrowComponent>(TEXT("ShotDirection"));
	//m_pShotSource->SetRelativeLocation(m_ShotOffset);
}


// Called when the game starts
void UWeapon::BeginPlay()
{
	Super::BeginPlay();

	m_pOwner = GetOwner();
	m_pSelfMovementComp = m_pOwner->FindComponentByClass<UCharacterMovementComponent>();
}

// Called every frame
void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_FireTimer > 0.f)
		m_FireTimer -= DeltaTime;

	if (CanShoot())
	{
		auto pirate = Cast<APirate>(m_pOwner);
		
		if (!m_IsPowerShot)
		{
			Shoot();

			if(pirate)
			{
				pirate->NotifyShoot();
			}
		}
		else
		{
			ShootCannonball();

			if(pirate)
			{
				pirate->NotifyPowerShot();
			}
		}
	}

	m_TriggerPulled = false;
}

void UWeapon::Shoot()
{
	TArray<FHitResult> outHits;

	FVector actorForward = m_pOwner->GetActorForwardVector();

	//VARIABLES
	float rayLength{ m_RayLength };
	float shootForce{ m_ImpulseForce };

	if (m_IsStrongerBlast)
	{
		rayLength *= 2;
		shootForce *= 2;
	}

	FVector startLoc = m_pOwner->GetActorLocation() + actorForward * m_ShotOffset.X;
	FVector endLoc = startLoc + (actorForward * rayLength);
	FVector midPoint = (startLoc + endLoc) / 2;

	//DEBUG
	//DrawDebugBox(GetWorld(), midPoint, FVector(rayLength / 2, m_ShotWidthHeight.X, m_ShotWidthHeight.Y),
	//	m_pOwner->GetActorRotation().Quaternion(), FColor::Red, false, 0.5f, 0, 2.5f);
	//DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, true, 1.f, 0, 5.f);


	m_BoxCollision = FCollisionShape::MakeBox(FVector(0, m_ShotWidthHeight.X, m_ShotWidthHeight.Y));

	bool isHit = GetWorld()->SweepMultiByObjectType(outHits, startLoc, endLoc,
		m_pOwner->GetActorRotation().Quaternion(), ECollisionChannel::ECC_PhysicsBody, m_BoxCollision);

	if (isHit)
	{
		for (auto& hit : outHits)
		{
			if (GEngine)
			{
				if (hit.GetActor()->ActorHasTag("Pirate"))
				{
					UCharacterMovementComponent* pMovementComp = hit.GetActor()->FindComponentByClass<UCharacterMovementComponent>();

					if (pMovementComp)
					{
						actorForward.Z = 1.f;
						pMovementComp->Launch(actorForward * shootForce);
						pMovementComp->HandlePendingLaunch();
					}
				}
				else if (hit.GetActor()->ActorHasTag("Barrel"))
				{
					UStaticMeshComponent* pMeshComp = Cast<UStaticMeshComponent>(hit.GetActor()->GetRootComponent());

					if (pMeshComp)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Ting3");

						actorForward.Z = 0.5f;
						FVector impulseVec = actorForward * shootForce * pMeshComp->GetMass();

						pMeshComp->AddImpulse(impulseVec);
					}
				}
			}
		}
	}

	actorForward *= -1;

	actorForward.Z = 0.1f;

	m_pSelfMovementComp->Launch(actorForward * m_ImpulseForce);
	m_pSelfMovementComp->HandlePendingLaunch();

	m_FireTimer += 1.0f / m_FireRate;
}

void UWeapon::ShootCannonball()
{
	FVector actorForward = m_pOwner->GetActorForwardVector();

	UWorld* world = GetWorld();

	if (world)
	{
		const FActorSpawnParameters spawnParameters;

		FVector spawnLocation = m_pOwner->GetActorLocation() + actorForward * m_PowerShotOffset;

		AActor* pProjectileActor = world->SpawnActor<AActor>(
			m_PowerShot, spawnLocation, FRotator(), spawnParameters);

		if (pProjectileActor)
		{
			APowerShotProjectile* pProjectile = Cast<APowerShotProjectile>(pProjectileActor);

			pProjectile->LaunchProjectile(actorForward);
		}
	}

	actorForward *= -1;
	actorForward.Z = 0.2f;

	m_pSelfMovementComp->Launch(actorForward * m_ImpulseForce * 2);
	m_pSelfMovementComp->HandlePendingLaunch();

	m_IsPowerShot = false;
}

void UWeapon::SetShootingTrue()
{
	m_TriggerPulled = true;
}

bool UWeapon::CanShoot()
{
	return m_FireTimer <= 0.f && m_TriggerPulled;
}