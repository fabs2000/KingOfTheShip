// Fill out your copyright notice in the Description page of Project Settings.


#include "EndScreenGameMode.h"
#include "CharGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"

AEndScreenGameMode::AEndScreenGameMode()
{

}

void AEndScreenGameMode::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
}

void AEndScreenGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_IsInit)
	{
		m_pGameInst = Cast<UCharGameInstance>(GetGameInstance());

		m_pWinningCharacterMesh = m_pGameInst->m_pWinningPlayer;

		for (auto loseP : m_pGameInst->m_pLosingPlayers)
		{
			m_pLosingPlayersMeshes.Add(loseP);
		}

		SetMeshes();

		m_IsInit = true;
	}
}

void AEndScreenGameMode::SetMeshes()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFloatingMesh::StaticClass(), m_pFloatingObjs);

	TArray<AActor*> tempObjs;

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::FromInt(m_pFloatingObjs.Num()));

	for (int32 id{}; id < m_pFloatingObjs.Num(); id++)
	{
		if (m_pFloatingObjs[id]->ActorHasTag(TEXT("Winner")))
		{
			USkeletalMeshComponent* pTempMesh = m_pFloatingObjs[id]->FindComponentByClass<USkeletalMeshComponent>();

			pTempMesh->SetSkeletalMesh(m_pWinningCharacterMesh);
		}

		else if (m_pFloatingObjs[id]->ActorHasTag(TEXT("Loser")))
		{
			tempObjs.Add(m_pFloatingObjs[id]);
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::FromInt(tempObjs.Num()));

	for (int32 id{}; id < tempObjs.Num(); id++)
	{
		USkeletalMeshComponent* pTempMesh = tempObjs[id]->FindComponentByClass<USkeletalMeshComponent>();

		pTempMesh->SetSkeletalMesh(m_pLosingPlayersMeshes[id]);
	}
}