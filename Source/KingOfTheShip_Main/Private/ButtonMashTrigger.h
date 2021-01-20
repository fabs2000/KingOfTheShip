// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "Engine/TargetPoint.h"
#include "ButtonMashTrigger.generated.h"

struct RecoveryPoint
{
	RecoveryPoint(ATargetPoint* pTargP, float dist) : pTargetPoint{ pTargP }, distToPlayer{ dist } {};

	ATargetPoint* pTargetPoint;
	float distToPlayer;
};

UCLASS()
class AButtonMashTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonMashTrigger();

	UPROPERTY(EditAnywhere)
		UShapeComponent* m_pTriggerComp;

	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> m_pTargetPoints;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	TArray<RecoveryPoint*> m_pRecoveryPoints;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector CalculateClosestRecoveryPoint(const FVector& piratePos);
};
