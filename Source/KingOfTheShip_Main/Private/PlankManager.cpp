#include "PlankManager.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

UPlankManager::UPlankManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlankManager::BeginPlay()
{
	Super::BeginPlay();

	m_pGameModeRef = Cast<AKingOfTheShip_MainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &UPlankManager::EnableDisableSpawner, m_EventCooldownTime, true);

	GetOwner()->GetAllChildActors(m_Planks);
	m_DestroyTimer = 1 / DestroyRate;
}

void UPlankManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pGameModeRef)
	{
		if (m_pGameModeRef->m_CannoballsEvent)
		{
			if (m_pGameModeRef)
				if (m_DestroyTimer > 0.f)
					m_DestroyTimer -= DeltaTime;

			if (m_DestroyTimer <= 0.f)
				DestoryPlank();
		}
	}
}

void UPlankManager::DestoryPlank()
{
	if (m_Planks.Num() == 0)
		return;

	m_DestroyTimer += 1.0f / DestroyRate;
	int randomTile = FMath::RandRange(0, m_Planks.Num() - 1);

	while (!Cast<APlank>(m_Planks[randomTile])->IsActive)
	{
		randomTile = FMath::RandRange(0, m_Planks.Num() - 1);
	}
	Cast<APlank>(m_Planks[randomTile])->PrepareDisable();
}

void UPlankManager::EnableDisableSpawner()
{
	m_pGameModeRef->m_CannoballsEvent = !m_pGameModeRef->m_CannoballsEvent;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "Plank Destruction Activation Called");
}