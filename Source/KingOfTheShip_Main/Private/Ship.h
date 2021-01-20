// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rocking.h"
#include "Engine/TargetPoint.h"
#include "Ship.generated.h"

UCLASS()
class AShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShip();

	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> m_RespawnPoints;

	UPROPERTY(EditAnywhere)
	float m_TiltTime = 3.f;

	UPROPERTY(EditAnywhere)
	float m_RockMultiplier = 3.f;

	void RockFast();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPlayerPosition(AActor* pPlayer);

private:
	//FTimerHandle m_TimerHandle;

	URocking* m_pRockingComp;
	float m_RockingTimer;
};
