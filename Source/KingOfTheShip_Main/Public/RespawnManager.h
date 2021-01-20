// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "RespawnManager.generated.h"

UCLASS()
class KINGOFTHESHIP_MAIN_API ARespawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARespawnManager();

	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> m_RespawnPoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPlayerPosition(AActor* pPlayer);

};
