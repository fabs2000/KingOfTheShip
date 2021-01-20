// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUpManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Chest.generated.h"

UCLASS()
class KINGOFTHESHIP_MAIN_API AChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void NotifyOpenChest();

	UFUNCTION(BlueprintCallable)
	void SpawnPickUp();
	
	void OpenChest();

private:

	class APickUpManager* m_pChestManager;
	bool m_CanOpenChest;
};
