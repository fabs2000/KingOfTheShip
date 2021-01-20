// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "FloatingMesh.generated.h"

/**
 * 
 */
UCLASS()
class AFloatingMesh : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AFloatingMesh();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
