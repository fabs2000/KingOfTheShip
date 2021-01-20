// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KrakenTentacle.h"
#include "KingOfTheShip_MainGameModeBase.h"
#include "Kraken.generated.h"

UCLASS()
class KINGOFTHESHIP_MAIN_API AKraken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKraken();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AKrakenTentacle> m_ToSpawn;

	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> m_SpawnPoints;

	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> m_RaycastSpawns;

	UPROPERTY(EditAnywhere)
		float m_SpawnRate = 5.f;

	UPROPERTY(EditAnywhere)
		int m_MaxTentacles = 2;

	UPROPERTY(EditAnywhere)
		float m_EventCooldownTime = 10.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void EnableDisableSpawner();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayKrakenSounds();

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnIndicator(ATargetPoint* spawnPoint);

private:
	AKingOfTheShip_MainGameModeBase* m_pGameModeRef;
	FTimerHandle m_TimerHandle;

	TArray<AActor*> m_pTentacles;

	float m_SpawnTimer;

	void SpawnTentacles();

};
