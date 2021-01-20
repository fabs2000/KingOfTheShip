// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pirate.h"
#include "FloatingMesh.h"
#include "EndScreenGameMode.generated.h"

class USkeletalMeshComponent;
class UCharGameInstance;

UCLASS()
class AEndScreenGameMode : public AGameModeBase
{
	GENERATED_BODY()

		AEndScreenGameMode();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    TArray<AActor*> m_pFloatingObjs;

    USkeletalMesh* m_pWinningCharacterMesh;
    TArray<USkeletalMesh*> m_pLosingPlayersMeshes;

    UCharGameInstance* m_pGameInst;

    bool m_IsInit = false;

    void SetMeshes();
};
