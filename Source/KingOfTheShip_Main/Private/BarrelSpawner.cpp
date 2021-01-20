#include "BarrelSpawner.h"
#include "Engine.h"
#include "Engine/TargetPoint.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

ABarrelSpawner::ABarrelSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	m_SpawnTimer = m_SpawnRate;
}

void ABarrelSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	m_pGameModeRef = Cast<AKingOfTheShip_MainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &ABarrelSpawner::EnableDisableSpawner, m_EventCooldownTime, true);
}


void ABarrelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i{}; i < m_pBarrels.Num(); i++)
	{
		if (m_pBarrels[i]->IsActorBeingDestroyed())
		{
			m_pBarrels[i] = nullptr;
			m_pBarrels.RemoveAt(i);
		}
	}


	if (m_pGameModeRef)
	{
		if (m_pGameModeRef->m_BarrelEvent)
		{
			if (m_SpawnTimer > 0.f)
				m_SpawnTimer -= DeltaTime;

			if (m_SpawnTimer < 2.f && m_SpawnTimer > 0.f)
			{
				if(!m_IsRandomPointChosen)
				{
					m_RandomSpawnPoint = FMath::RandRange(0, m_SpawnPoints.Num() - 1);
					m_IsRandomPointChosen = true;
				}
				SpawnIndicator(m_SpawnPoints[m_RandomSpawnPoint]);
			}

			if (m_SpawnTimer <= 0.f)
				SpawnBarrels();
		}
	}
}

void ABarrelSpawner::SpawnBarrels()
{
	if (m_SpawnPoints.Num() <= 0)
		return;

	m_SpawnTimer += m_SpawnRate;
	m_IsRandomPointChosen = false;

	if (m_pBarrels.Num() >= m_MaxBarrels)
		return;


	if (m_ToSpawn)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			const FActorSpawnParameters SpawnParameters;

			const FRotator rotator = m_SpawnPoints[m_RandomSpawnPoint]->GetTransform().GetRotation().Rotator();
			const FVector spawnLocation = m_SpawnPoints[m_RandomSpawnPoint]->GetTransform().GetLocation();

			auto barrel = world->SpawnActor<AStunBarrel>(m_ToSpawn, spawnLocation, rotator, SpawnParameters);
			
			if (barrel)
			{
				FVector impulseVec = m_SpawnPoints[m_RandomSpawnPoint]->GetActorForwardVector() * m_InitialBarrelImpulse;
				auto mesh = barrel->FindComponentByClass<UStaticMeshComponent>();

				mesh->AddImpulse(impulseVec * mesh->GetMass());
			}

			m_pBarrels.Add(barrel);
		}
	}
}

void ABarrelSpawner::EnableDisableSpawner()
{
	m_pGameModeRef->m_BarrelEvent = !m_pGameModeRef->m_BarrelEvent;
	//GEngine->AddOnScreenDebugMessage(-1,15.f,FColor::Green, "Barrel Activation Called");
}