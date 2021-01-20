// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonMashTrigger.h"
#include "Components/BoxComponent.h"
#include "Pirate.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Algo/MinElement.h"
#include "GameFramework/Controller.h"

// Sets default values
AButtonMashTrigger::AButtonMashTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pTriggerComp = this->CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));

}

// Called when the game starts or when spawned
void AButtonMashTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_pTriggerComp->OnComponentBeginOverlap.AddDynamic(
		this, &AButtonMashTrigger::OnBeginOverlap);

	//DrawDebugBox(GetWorld(), GetActorLocation(), 
	//	GetComponentsBoundingBox().GetExtent(), 
	//	FColor::Green, true, -1, 0, 5);
}

// Called every frame
void AButtonMashTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonMashTrigger::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != this))
	{
		if (OtherActor->ActorHasTag("Pirate"))
		{
			APirate* pPirate = Cast<APirate>(OtherActor);

			if (pPirate != nullptr)
			{
				UCharacterMovementComponent* pPirateMovement = pPirate->FindComponentByClass<UCharacterMovementComponent>();

				if (pPirateMovement != nullptr)
				{
					pPirateMovement->GravityScale = 0.f;
					pPirateMovement->Velocity = FVector(0,0,0);
					pPirateMovement->SetMovementMode(EMovementMode::MOVE_None);
				}

				FVector closestPoint = CalculateClosestRecoveryPoint(pPirate->GetActorLocation());

				pPirate->SetActorLocation(closestPoint);
				pPirate->SetIsInWater(true);
			}
		}
	}
}

FVector AButtonMashTrigger::CalculateClosestRecoveryPoint(const FVector& piratePos)
{
	for (int i{}; i < m_pTargetPoints.Num(); ++i)
	{
		float dist = FVector::Distance(piratePos, m_pTargetPoints[i]->GetActorLocation());

		m_pRecoveryPoints.Add(new RecoveryPoint(m_pTargetPoints[i], dist));
	}

	RecoveryPoint* closestPoint = *Algo::MinElement(m_pRecoveryPoints, [](RecoveryPoint* pPoint1, RecoveryPoint* pPpoint2)
		{
			return pPoint1->distToPlayer < pPpoint2->distToPlayer;
		});

	return closestPoint->pTargetPoint->GetActorLocation();
}
