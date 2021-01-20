// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Chest.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "KingOfTheShip_MainGameModeBase.h"
#include "ChestManager.generated.h"

struct SpawnSpot
{
	class ATargetPoint* pSpawnPoint;
	AChest* pChest = nullptr;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KINGOFTHESHIP_MAIN_API AChestManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AChestManager();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AChest> m_ToSpawn;

	UPROPERTY(EditAnywhere)
	TArray<class ATargetPoint*> m_SpawnPoints;
	
	UPROPERTY(EditAnyWhere)
	float m_SpawnRate = 5.f;

	UPROPERTY(EditAnyWhere)
	int m_MaxChests = 2;

	UPROPERTY(EditAnywhere)
		float m_EventCooldownTime = 10.f;

	TArray<AActor*>& GetChests(){ return m_Chests;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnChest();

	UFUNCTION()
	void EnableDisableSpawner();

private:
	AKingOfTheShip_MainGameModeBase* m_pGameModeRef;
	FTimerHandle m_TimerHandle;

	TArray<AActor*> m_Chests;
	TArray<SpawnSpot> m_SpawnSpots;

	float m_SpawnTimer;	
};
