// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "Rum.generated.h"

/**
 * 
 */
UCLASS()
class ARum : public APickUpBase
{
	GENERATED_BODY()

public:
	ARum();

protected:
	virtual void BeginPlay() override;
};
