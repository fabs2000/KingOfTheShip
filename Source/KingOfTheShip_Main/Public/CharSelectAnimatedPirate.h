// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimBlueprint.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharSelectAnimatedPirate.generated.h"

UCLASS()
class KINGOFTHESHIP_MAIN_API ACharSelectAnimatedPirate : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharSelectAnimatedPirate();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* m_pSkeletalMesh;

	UPROPERTY(BlueprintReadOnly)
	bool m_IsSelected;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetIsSelected(bool isSelected) { m_IsSelected = isSelected; }
};
