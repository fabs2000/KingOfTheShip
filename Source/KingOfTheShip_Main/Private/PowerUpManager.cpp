// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpManager.h"
#include "Engine.h"

// Sets default values for this component's properties
UPowerUpManager::UPowerUpManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	m_SpawnTimer = m_SpawnRate;
}


// Called when the game starts
void UPowerUpManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPowerUpManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_SpawnTimer > 0.f)
		m_SpawnTimer -= DeltaTime;

	if (m_SpawnTimer <= 0.f)
		SpawnPowerUp();
	// ...

}

void UPowerUpManager::SpawnPowerUp()
{
	// Reset timer
	m_SpawnTimer += m_SpawnRate;

	// Only spawn a PowerUp when the max powerups isnt reached
	if(m_Chests.Num() >= m_MaxChests)
		return;

	if(m_ToSpawn)
	{
		UWorld* world = GetWorld();
		if(world)
		{
			const FActorSpawnParameters SpawnParameters;
			
			const FRotator rotator;
			const FVector spawnLocation = FVector{-130,450,1800};

			auto chest = world->SpawnActor<AChest>(m_ToSpawn, spawnLocation, rotator, SpawnParameters);

			// Add a reference to the manager
			m_Chests.Push(chest);
		}
	}
	//m_Chests.Add(newChest);
}