// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharSelectorInd.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharSelectionManager.generated.h"


UCLASS()
class KINGOFTHESHIP_MAIN_API ACharSelectionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharSelectionManager();

	UPROPERTY(EditAnywhere)
	int m_Players;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> m_pPirates;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACharSelectorInd> m_ToSpawn;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> m_Materials;

	UFUNCTION(BlueprintCallable)
	void AdvanceLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void CheckCharactorsSelected();
	void PlacementIndicators();
	void UpdateCharAnimations();

	UPROPERTY(EditAnywhere)
	TArray<AActor*> m_CharSelectors;
};
