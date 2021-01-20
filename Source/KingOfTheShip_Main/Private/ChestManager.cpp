#include "ChestManager.h"
#include "Engine.h"
#include "Engine/TargetPoint.h"
#include "TimerManager.h"

AChestManager::AChestManager()
{
	PrimaryActorTick.bCanEverTick = true;
	m_SpawnTimer = m_SpawnRate;
}

void AChestManager::BeginPlay()
{
	Super::BeginPlay();

	m_SpawnSpots.SetNum(m_SpawnPoints.Num());

	for (size_t i{}; i < m_SpawnPoints.Num(); i++)
	{
		m_SpawnSpots[i].pSpawnPoint = m_SpawnPoints[i];
	}

	m_pGameModeRef = Cast<AKingOfTheShip_MainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &AChestManager::EnableDisableSpawner, m_EventCooldownTime, true);
}

void AChestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i{}; i < m_Chests.Num(); i++)
	{
		if (m_Chests[i]->IsActorBeingDestroyed())
		{
			m_Chests[i] = nullptr;
			m_Chests.RemoveAt(i);
		}
	}

	if (m_pGameModeRef)
	{
		if (m_pGameModeRef->m_ChestsEvent)
		{
			if (m_SpawnTimer > 0.f)
				m_SpawnTimer -= DeltaTime;

			if (m_SpawnTimer <= 0.f)
				SpawnChest();
		}
	}
}

void AChestManager::SpawnChest()
{
	if (m_SpawnPoints.Num() <= 0)
		return;

	const int randomSpawnPoint = FMath::RandRange(0, m_SpawnPoints.Num() - 1);

	m_SpawnTimer += m_SpawnRate;

	if (m_Chests.Num() >= m_MaxChests)
		return;

	// if there is already a chest on that spot return and dont spawn a chest
	//if(m_SpawnSpots[randomSpawnPoint].pChest != nullptr)
	//	return;

	if (m_ToSpawn)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			const FActorSpawnParameters SpawnParameters;

			const FRotator rotator = m_SpawnSpots[randomSpawnPoint].pSpawnPoint->GetTransform().GetRotation().Rotator();
			const FVector spawnLocation = m_SpawnSpots[randomSpawnPoint].pSpawnPoint->GetTransform().GetLocation();

			auto chest = world->SpawnActor<AChest>(m_ToSpawn, spawnLocation, rotator, SpawnParameters);

			m_SpawnSpots[randomSpawnPoint].pChest = chest;
			m_Chests.Add(chest);
		}
	}
}

void AChestManager::EnableDisableSpawner()
{
	m_pGameModeRef->m_ChestsEvent = !m_pGameModeRef->m_ChestsEvent;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "Chest Activation Called");
}