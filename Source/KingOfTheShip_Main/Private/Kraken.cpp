#include "Kraken.h"
#include "Engine.h"
#include "Engine/TargetPoint.h"
#include "TimerManager.h"

AKraken::AKraken()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SpawnTimer = m_SpawnRate;
}

void AKraken::BeginPlay()
{
	Super::BeginPlay();
	
	m_pGameModeRef = Cast<AKingOfTheShip_MainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &AKraken::EnableDisableSpawner, m_EventCooldownTime, true);
}

void AKraken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i{}; i < m_pTentacles.Num(); i++)
	{
		if (m_pTentacles[i]->IsActorBeingDestroyed())
		{
			m_pTentacles[i] = nullptr;
			m_pTentacles.RemoveAt(i);
		}
	}

	if (m_pGameModeRef)
	{
		if (m_pGameModeRef->m_KrakenEvent)
		{
			if (m_SpawnTimer > 0.f)
				m_SpawnTimer -= DeltaTime;

			if (m_SpawnTimer <= 0.f)
				SpawnTentacles();
		}
	}
}

void AKraken::SpawnTentacles()
{
	if (m_SpawnPoints.Num() <= 0)
		return;

	const int randId = FMath::RandRange(0, m_SpawnPoints.Num() - 1);

	auto randSpawnPoint = m_SpawnPoints[randId];

	m_SpawnTimer += m_SpawnRate;

	if (m_pTentacles.Num() >= m_MaxTentacles)
		return;

	if (m_ToSpawn)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			const FActorSpawnParameters SpawnParameters;

			const FRotator rotator = randSpawnPoint->GetTransform().GetRotation().Rotator();
			const FVector spawnLocation = randSpawnPoint->GetTransform().GetLocation();

			auto barrel = world->SpawnActor<AKrakenTentacle>(m_ToSpawn, spawnLocation, rotator, SpawnParameters);
			if (barrel)
			{
				if (FVector::Distance(randSpawnPoint->GetActorLocation(), m_RaycastSpawns[0]->GetActorLocation()) < 
					FVector::Distance(randSpawnPoint->GetActorLocation(), m_RaycastSpawns[1]->GetActorLocation()))
				{
					barrel->SetRayCastOrigin(m_RaycastSpawns[0]);
					//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Left");
					SpawnIndicator(m_RaycastSpawns[0]);
				}
				else
				{
					barrel->SetRayCastOrigin(m_RaycastSpawns[1]);
					//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Right");
					SpawnIndicator(m_RaycastSpawns[1]);
				}

				m_pTentacles.Add(barrel);
			}
		}
	}
}

void AKraken::EnableDisableSpawner()
{
	m_pGameModeRef->m_KrakenEvent = !m_pGameModeRef->m_KrakenEvent;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "Kraken Activation Called");

	PlayKrakenSounds();
}