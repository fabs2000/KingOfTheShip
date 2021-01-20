// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KingOfTheShip_MainGameModeBase.h"
#include "CustomCameraActor.generated.h"

UCLASS()
class KINGOFTHESHIP_MAIN_API ACustomCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomCameraActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AActor* m_pRenderTarget;

	UPROPERTY(EditAnywhere)
		float m_XOffset = 500;

	UPROPERTY(EditAnywhere)
		float m_ZOffset = 250;

	UPROPERTY(EditAnywhere)
		float m_CamSpeed = 5.f;

private:

	//AKingOfTheShip_MainGameModeBase* m_pCurrentGameMode;
	//TMap<FString, APlayerController*> m_pPlayers2;

	TArray<AActor*> m_pPlayers;
	TArray<APlayerController*> m_pPlayerControllers;

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
	float m_ZoomSpeed;

	bool m_IsInitializing = true;
	bool m_CanMove = false;
};
