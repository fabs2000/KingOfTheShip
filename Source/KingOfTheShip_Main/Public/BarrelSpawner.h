// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "StunBarrel.h"
#include "KingOfTheShip_MainGameModeBase.h"
#include "BarrelSpawner.generated.h"

UCLASS()
class KINGOFTHESHIP_MAIN_API ABarrelSpawner : public AActor
{
	GENERATED_BODY()

public:
	ABarrelSpawner();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AStunBarrel> m_ToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ATargetPoint*> m_SpawnPoints;

	UPROPERTY(EditAnywhere)
	float m_SpawnRate = 5.f;

	UPROPERTY(EditAnywhere)
	int m_MaxBarrels = 6;

	UPROPERTY(EditAnywhere)
	float m_InitialBarrelImpulse = 500.f;

	UPROPERTY(EditAnywhere)
	float m_EventCooldownTime = 10.f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void EnableDisableSpawner();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnIndicator(ATargetPoint* spawnPoint);
	

private:

	AKingOfTheShip_MainGameModeBase* m_pGameModeRef;
	FTimerHandle m_TimerHandle;

	TArray<AActor*> m_pBarrels;

	float m_SpawnTimer;
	int m_RandomSpawnPoint;
	bool m_IsRandomPointChosen = false;

	void SpawnBarrels();
};
