#include "KingOfTheShip_MainGameModeBase.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Misc/StringFormatArg.h"
#include "CharGameInstance.h"

AKingOfTheShip_MainGameModeBase::AKingOfTheShip_MainGameModeBase()
{
	//Init P1 Mesh

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAssetP1(
		TEXT("/Game/Animations/Characters/Captn/Character_Captn_SK.Character_Captn_SK"));
	if (meshAssetP1.Succeeded())
	{
		m_pMeshesToAdd.Add(meshAssetP1.Object);
	}

	//Init P2 Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAssetP2(
		TEXT("/Game/Animations/Characters/Parry/Character_Parry_SK.Character_Parry_SK"));
	if (meshAssetP2.Succeeded())
	{
		m_pMeshesToAdd.Add(meshAssetP2.Object);
	}

	//Init P3 Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAssetP3(
		TEXT("/Game/Animations/Characters/Sharky/Character_Sharky_SK.Character_Sharky_SK"));
	if (meshAssetP3.Succeeded())
	{
		m_pMeshesToAdd.Add(meshAssetP3.Object);
	}
	//Init P4 Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAssetP4(
		TEXT("/Game/Animations/Characters/Shrimp/Character_Shrimp_SK.Character_Shrimp_SK"));
	if (meshAssetP4.Succeeded())
	{
		m_pMeshesToAdd.Add(meshAssetP4.Object);
	}

}

void AKingOfTheShip_MainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
}

void AKingOfTheShip_MainGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_IsGameOver)
	{
		if (!m_ArePlayersInit)
		{
			SetMeshes();

			m_ArePlayersInit = true;

			m_ActivePlayers = m_pPlayers.Num();
		}

		for (APirate* pPirate : m_pPirates)
		{
			if (pPirate->GetIsToBeSubtracted())
			{
				if (!pPirate->IsActorTickEnabled())
				{
					//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "One less");
					
					--m_ActivePlayers;

					pPirate->SetIsToBeSubstracted(false);

					m_pGameInst->m_pLosingPlayers.Add(pPirate->GetMesh()->SkeletalMesh);
				}
			}
		}

		if (m_ActivePlayers == 1)
		{
			m_IsGameOver = true;

			GetWorld()->GetWorldSettings()->SetTimeDilation(0.3f);

			for (APirate* pPirate : m_pPirates)
			{
				if (pPirate->IsActorTickEnabled())
				{
					m_pGameInst->m_pWinningPlayer = pPirate->GetMesh()->SkeletalMesh;
				}
			}
		}
	}
	else
	{
		m_TimerToLevel += DeltaTime;

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(m_TimerToLevel));

		if (m_TimerToLevel >= 1.5f)
		{
			GoToEndScreen();
		}
	}

	m_Clock += DeltaTime;
}

void AKingOfTheShip_MainGameModeBase::SetMeshes()
{
	UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), m_PirateType, m_pPlayers);

	m_pGameInst = Cast<UCharGameInstance>(GetGameInstance());
	
	for (int i{}; i < m_pPlayers.Num(); i++)
	{
		APirate* pPirate = Cast<APirate>(m_pPlayers[i]);

		m_pPirates.Add(pPirate);
		m_pPirateMeshes.Add(m_pPlayers[i]->FindComponentByClass<USkeletalMeshComponent>());

		if(m_pGameInst)
		{
			switch(m_pGameInst->m_SelectedCharacter[i])
			{
			case 0:
				pPirate->m_PirateType = PirateType::Captn;
				break;
			case 1:
				pPirate->m_PirateType = PirateType::Parry;
				break;
			case 2:
				pPirate->m_PirateType = PirateType::Sharky;
				break;
			case 3:
				pPirate->m_PirateType = PirateType::Shrimp;
				break;
			}
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(m_pMeshesToAdd.Num()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(m_pPlayers.Num()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(m_pPirateMeshes.Num()));

	if(m_pGameInst)
	{
		for (int32 id{}; id < m_pPirateMeshes.Num(); id ++)
		{
			m_pPirateMeshes[id]->SetSkeletalMesh(m_pMeshesToAdd[m_pGameInst->m_SelectedCharacter[id]]);
			m_pPirateMeshes[id]->SetWorldScale3D(FVector(1.2f));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "GameInstance was nullptr");
		m_pPirateMeshes[0]->SetSkeletalMesh(m_pMeshesToAdd[0]);
		m_pPirateMeshes[0]->SetWorldScale3D(FVector(1.2f));
	}
}

void AKingOfTheShip_MainGameModeBase::GoToEndScreen()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("EndScreenLevel"));
}
