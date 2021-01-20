// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pirate.h"
#include "CharGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UCharGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int> m_SelectedCharacter;

	USkeletalMesh* m_pWinningPlayer;

	TArray<USkeletalMesh*> m_pLosingPlayers;
};
