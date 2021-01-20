// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NotificationsManager.generated.h"

UCLASS()
class KINGOFTHESHIP_MAIN_API ANotificationsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANotificationsManager();

	UFUNCTION(BlueprintImplementableEvent)
	void NotifyPlayerInWater(class APirate* pirate);

	UFUNCTION(BlueprintImplementableEvent)
	void NotifyPlayerOutOfWater(class APirate* pirate);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
