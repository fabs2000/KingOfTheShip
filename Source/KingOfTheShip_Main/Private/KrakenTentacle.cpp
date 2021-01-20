#include "KrakenTentacle.h"
#include "DrawDebugHelpers.h"
#include "WorldCollision.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AKrakenTentacle::AKrakenTentacle()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));

	m_pBody->SetupAttachment(RootComponent);
}

void AKrakenTentacle::BeginPlay()
{
	Super::BeginPlay();

	m_pShipRef = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "SpawnedKraken");
}

void AKrakenTentacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKrakenTentacle::LaunchObjects()
{
	TArray<FHitResult> outHits;

	if (!m_pRayCastOrigin)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Origin is null");
		return;
	}

	FVector actorForward = m_pRayCastOrigin->GetActorForwardVector();

	FVector startLoc = m_pRayCastOrigin->GetActorLocation();
	FVector endLoc = startLoc + (actorForward * m_RayCastLength);
	FVector midPoint = (startLoc + endLoc) / 2;

	//DEBUG
	//DrawDebugBox(GetWorld(), midPoint, FVector(m_RayCastLength / 2, m_RaycastAreaDimensions.X, m_RaycastAreaDimensions.Y),
	//	m_pRayCastOrigin->GetActorRotation().Quaternion(), FColor::Red, false, 0.5f, 0, 2.5f);

	FCollisionShape boxCollision = FCollisionShape::MakeBox(FVector(0, m_RaycastAreaDimensions.X, m_RaycastAreaDimensions.Y));

	bool isHit = GetWorld()->SweepMultiByObjectType(outHits, startLoc, endLoc,
		m_pRayCastOrigin->GetActorRotation().Quaternion(), ECollisionChannel::ECC_PhysicsBody, boxCollision);

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
						pMovementComp->Launch(actorForward * m_LaunchForce);
						pMovementComp->HandlePendingLaunch();
					}
				}
			}
		}
	}

	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(Shake, 0.9f);

	m_pShipRef->RockFast();
}
