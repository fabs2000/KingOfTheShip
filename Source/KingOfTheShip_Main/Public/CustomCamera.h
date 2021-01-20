// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "KingOfTheShip_MainGameModeBase.h"
#include "CustomCamera.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFTHESHIP_MAIN_API ACustomCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float m_XOffset = 500;

	UPROPERTY(EditAnywhere)
		float m_ZOffset = 250;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	AKingOfTheShip_MainGameModeBase* m_pCurrentGameMode;
	TMap<FString, APlayerController*> m_pPlayers;

	//Camera Movement
	//bool IsPlayerOutOfView(APlayerController* pPlayer);

	bool CheckZoomOut(APlayerController* pPlayer);
	bool CheckZoomIn(APlayerController* pPlayer);
	void MoveCameraBack();
	void MoveCameraForward();

	FVector m_StartCamPos;
	FVector m_PosOffset;
	float m_StartZoomingOut;
	float m_StartZoomingIn;
	FVector m_MaxEndCamPos;

};
