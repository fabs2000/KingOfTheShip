// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PowerShot.generated.h"

UCLASS()
class APowerShot : public APickUpBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerShot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
