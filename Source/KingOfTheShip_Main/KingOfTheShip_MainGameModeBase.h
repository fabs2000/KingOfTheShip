// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pirate.h"
#include "KingOfTheShip_MainGameModeBase.generated.h"

class UCharGameInstance;

UCLASS()
class KINGOFTHESHIP_MAIN_API AKingOfTheShip_MainGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

        AKingOfTheShip_MainGameModeBase();

public:

    UPROPERTY(EditAnywhere)
    TSubclassOf<APirate> m_PirateType;
	
	UPROPERTY(BlueprintReadWrite)
	float m_Clock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
    bool m_BarrelEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
    bool m_KrakenEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
    bool m_CannoballsEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
    bool m_ChestsEvent;


protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    //CONTAINERS
    TArray<AActor*> m_pPlayers;
    TArray<APirate*> m_pPirates;
    TArray<USkeletalMesh*> m_pMeshesToAdd;
    TArray<USkeletalMeshComponent*> m_pPirateMeshes;

    //INIT
    void SetMeshes();
    bool m_ArePlayersInit = false;
    
    //PER FRAME INFO
    int32 m_ActivePlayers;
    bool m_IsGameOver;

    //LOAD NEXT LEVEL
    float m_TimerToLevel;
    UCharGameInstance* m_pGameInst;
    void GoToEndScreen();
};
