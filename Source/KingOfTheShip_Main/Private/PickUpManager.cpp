// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpManager.h"
#include "Engine.h"

// Sets default values
APickUpManager::APickUpManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUpManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for(int i{}; i < m_PickUps.Num(); i++)
	{
		if(m_PickUps[i]->IsActorBeingDestroyed())
		{
			m_PickUps.RemoveAt(i);
		}
	}
}

void APickUpManager::SpawnPickUp(const FVector& pos)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "PickUp Spawned");

	const int randomPowerUp = FMath::RandRange(0, m_ToSpawn.Num() - 1);

	
	if(m_ToSpawn[randomPowerUp])
	{
		UWorld* world = GetWorld();
		if(world)
		{
			const FActorSpawnParameters SpawnParameters;
			
			const FRotator rotator;
			const FVector spawnLocation = pos;

			auto pickUp = world->SpawnActor<APickUpBase>(m_ToSpawn[randomPowerUp], spawnLocation, rotator, SpawnParameters);

			m_PickUps.Add(pickUp);
		}
	}
}

