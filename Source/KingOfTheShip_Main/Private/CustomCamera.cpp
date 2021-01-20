// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/CustomCamera.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

void ACustomCamera::BeginPlay()
{
	m_pCurrentGameMode = Cast<AKingOfTheShip_MainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//m_pPlayers = m_pCurrentGameMode->GetPlayers();

	m_pPlayers.Find("Player1");

	m_StartCamPos = FVector(GetActorLocation());

	m_MaxEndCamPos = FVector(m_StartCamPos.X - m_XOffset, m_StartCamPos.Y, m_StartCamPos.Z + m_ZOffset);
	m_StartZoomingIn = 0.5f;
	m_StartZoomingOut = 1.f;
}

void ACustomCamera::Tick(float DeltaTime)
{	
	for (TPair<FString, APlayerController*> player : m_pPlayers)
	{
		if (CheckZoomOut(player.Value))
		{
			MoveCameraBack();
			UE_LOG(LogTemp, Warning, TEXT("MovingBack"));
			return;
		}
	}
	for (TPair<FString, APlayerController*> player : m_pPlayers)
	{
		if(CheckZoomIn(player.Value))
		{
			MoveCameraForward();
			UE_LOG(LogTemp, Warning, TEXT("MovingForward"));
			return;
		}
	}
}

//bool ACustomCamera::IsPlayerOutOfView(APlayerController* pPlayer)
//{
//	FVector2D screenLocation;
//	pPlayer->ProjectWorldLocationToScreen(pPlayer->GetPawn()->GetActorLocation(), screenLocation);
//
//	int32 screenWidth = 0;
//	int32 screenHeight = 0;
//	pPlayer->GetViewportSize(screenWidth, screenHeight);
//
//	int32 ScreenX = (int32)screenLocation.X;
//	
//	return ScreenX >= 0 && ScreenX < screenWidth;
//}

bool ACustomCamera::CheckZoomOut(APlayerController* pPlayer)
{
	FVector2D screenLocation;
	pPlayer->ProjectWorldLocationToScreen(pPlayer->GetPawn()->GetActorLocation(), screenLocation);

	int32 screenWidth = 0;
	int32 screenHeight = 0;
	pPlayer->GetViewportSize(screenWidth, screenHeight);

	const int32 screenX = (int32)screenLocation.X;

	const int32 minX{int32((1 - m_StartZoomingOut) * screenWidth)};
	const int32 maxX{int32(m_StartZoomingOut * screenWidth)};
	
	return screenX <= minX && screenX > maxX;
}

bool ACustomCamera::CheckZoomIn(APlayerController* pPlayer)
{
	FVector2D screenLocation;
	pPlayer->ProjectWorldLocationToScreen(pPlayer->GetPawn()->GetActorLocation(), screenLocation);

	int32 screenWidth = 0;
	int32 screenHeight = 0;
	pPlayer->GetViewportSize(screenWidth, screenHeight);

	const int32 screenX = (int32)screenLocation.X;

	const int32 minX{int32((1 - m_StartZoomingIn) * screenWidth)};
	const int32 maxX{int32(m_StartZoomingIn * screenWidth)};
	
	return screenX >= minX && screenX < maxX;
}

void ACustomCamera::MoveCameraBack()
{
	FVector actorPos = GetActorLocation();

	if (actorPos.X > m_MaxEndCamPos.X && actorPos.Z < m_MaxEndCamPos.Z)
	{
		AddActorWorldOffset(FVector(-1,0,1), true);
	}
}

void ACustomCamera::MoveCameraForward()
{
	FVector actorPos = GetActorLocation();
	
	if (actorPos.X < m_StartCamPos.X && actorPos.Z > m_StartCamPos.Z)
	{
		AddActorWorldOffset(FVector(1, 0, -1), true);
	}
}