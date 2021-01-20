// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerShotProjectile.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APowerShotProjectile::APowerShotProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pProjMovement = this->CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	m_pStaticMesh = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//m_pSphereCollision = this->CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	SetRootComponent(m_pStaticMesh);
	//m_pSphereCollision->SetupAttachment(RootComponent);

	m_pProjMovement->UpdatedComponent = m_pStaticMesh;
	m_pProjMovement->bShouldBounce = true;
	m_pProjMovement->Bounciness = 0.2f;
}

// Called when the game starts or when spawned
void APowerShotProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	m_pStaticMesh->OnComponentHit.AddDynamic(this, &APowerShotProjectile::OnHit);
}

// Called every frame
void APowerShotProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerShotProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComponent)
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, "yes");	
		
		UCharacterMovementComponent* pMovementComp = OtherActor->FindComponentByClass<UCharacterMovementComponent>();

		if (pMovementComp)
		{
			//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, "yes2");
			m_ShotDirection.Z = 0.85f;
			pMovementComp->Launch(m_ShotDirection * m_ShotStrength);
			pMovementComp->HandlePendingLaunch();

			Destroy();
		}
	}
}

void APowerShotProjectile::LaunchProjectile(const FVector& direction)
{
	if (m_pProjMovement)
	{
		m_pProjMovement->Velocity = direction * m_pProjMovement->InitialSpeed;
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::SanitizeFloat(m_pProjMovement->InitialSpeed));
		m_ShotDirection = direction;
	}
}

