// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUpBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpManager.generated.h"

UCLASS()
class KINGOFTHESHIP_MAIN_API APickUpManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APickUpManager();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class APickUpBase>> m_ToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnPickUp(const FVector& pos);

private:
	
	UPROPERTY(EditAnyWhere)
	TArray<AActor*> m_PickUps;
};
