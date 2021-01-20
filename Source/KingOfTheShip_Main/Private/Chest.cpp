// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CanOpenChest = true;
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();

	m_pChestManager = Cast<APickUpManager>(UGameplayStatics::GetActorOfClass(GetWorld(), APickUpManager::StaticClass()));
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z < 0.f)
	{
		Destroy();
	}
}

void AChest::SpawnPickUp()
{
	m_pChestManager->SpawnPickUp(GetActorLocation());
}

void AChest::OpenChest()
{
	if (m_CanOpenChest)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "OpenChest");

		if (!m_pChestManager)
			return;

		NotifyOpenChest();

		m_CanOpenChest = false;
	}
}

