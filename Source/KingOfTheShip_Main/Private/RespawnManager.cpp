// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnManager.h"

ARespawnManager::ARespawnManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARespawnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARespawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARespawnManager::SetPlayerPosition(AActor* pPlayer)
{
	int64 rndSpawnID = FMath::RandRange(0, 1);

	pPlayer->SetActorLocation(m_RespawnPoints[rndSpawnID]->GetActorLocation());
}

