// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomCameraActor.h"
#include "..\Public\CustomCameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include <string>

// Sets default values
ACustomCameraActor::ACustomCameraActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACustomCameraActor::BeginPlay()
{
	Super::BeginPlay();

	m_StartCamPos = FVector(m_pRenderTarget->GetActorLocation());
	m_MaxEndCamPos = FVector(m_StartCamPos.X - m_XOffset, m_StartCamPos.Y, m_StartCamPos.Z + m_ZOffset);

	m_StartZoomingIn = 0.7f;
	m_StartZoomingOut = 0.8f;
}

// Called every frame
void ACustomCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// reset zoomSpeed each frame;
	m_ZoomSpeed = 1;
	
	if (m_IsInitializing)
	{
		UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), APlayerController::StaticClass(), m_pPlayers);

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(m_pPlayers.Num()));

		for (auto pPC : m_pPlayers)
		{
			auto pPlayer = Cast<APlayerController>(pPC);
			if(pPlayer)
			{
				m_pPlayerControllers.Add(pPlayer);				
			}
		}

		m_pPlayerControllers[0]->SetViewTarget(m_pRenderTarget);

		m_IsInitializing = false;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, std::to_string(m_pPlayers.Num()).c_str());

	for (int i{}; i < m_pPlayerControllers.Num(); i++)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, ("Player" + std::to_string(i)).c_str());
		if(!m_pPlayerControllers[i])
			continue;
		if (CheckZoomOut(m_pPlayerControllers[i]))
		{
			MoveCameraBack();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "MoveBack");
			return;
		}
	}

	int counter{};
	for (auto player : m_pPlayerControllers)
	{
		if(CheckZoomIn(player))
		{
			counter++;
		}
	}
	if(counter == m_pPlayerControllers.Num())
	{
		MoveCameraForward();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "MoveForward");
	}

	//m_CanMove = false;
	//
	//for (auto playerCont : m_pPlayerControllers)
	//{
	//	//if ((IsPlayerOutOfView(m_pPlayerControllers[0]) || IsPlayerOutOfView(m_pPlayerControllers[1])) || (IsPlayerOutOfView(m_pPlayerControllers[2]) || IsPlayerOutOfView(m_pPlayerControllers[3])))
	//	//{
	//	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "MoveBack");
	//	//	MoveCameraBack();
	//	//}
	//	//else
	//	//{
	//	//	MoveCameraForward();
	//	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "MoveForward");
	//	//}

	//	if (IsPlayerOutOfView(playerCont))
	//	{
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "MoveBack");
	//		m_CanMove = true;
	//		MoveCameraBack();
	//	}
	//}

	//if(!m_CanMove)
	//{
	//	MoveCameraForward();
	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "MoveForward");
	//}

}

//bool ACustomCameraActor::IsPlayerOutOfView(APlayerController* pPlayer)
//{
//	FVector2D ScreenLocation;
//	m_pPlayerControllers[0]->ProjectWorldLocationToScreen(pPlayer->GetPawn()->GetActorLocation(), ScreenLocation);
//
//	int32 ScreenWidth = 0;
//	int32 ScreenHeight = 0;
//	m_pPlayerControllers[0]->GetViewportSize(ScreenWidth, ScreenHeight);
//
//	int32 ScreenXPos = (int32)ScreenLocation.X;
//
//	return !(ScreenXPos >= (ScreenWidth / 4) && ScreenXPos <= ((3 * ScreenWidth) / 4));
//}

bool ACustomCameraActor::CheckZoomOut(APlayerController* pPlayer)
{
	FVector2D screenLocation;
	m_pPlayerControllers[0]->ProjectWorldLocationToScreen(pPlayer->GetPawn()->GetActorLocation(), screenLocation);

	int32 screenWidth = 0;
	int32 screenHeight = 0;
	pPlayer->GetViewportSize(screenWidth, screenHeight);

	const int32 screenX = (int32)screenLocation.X;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(screenX));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, std::to_string(screenX).c_str());


	const int32 minX{int32((1 - m_StartZoomingOut) * screenWidth)};
	const int32 maxX{int32(m_StartZoomingOut * screenWidth)};

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(minX));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(maxX));
	
	if(screenX <= minX)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Should be moving out");
		m_ZoomSpeed = (minX - screenX) / float(minX);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, std::to_string(m_ZoomSpeed).data());
		return true;
	}

	if(screenX > maxX)
	{
		m_ZoomSpeed = (screenX - maxX) / float(minX);
		return true;
	}

	return false;
}

bool ACustomCameraActor::CheckZoomIn(APlayerController* pPlayer)
{
	FVector2D screenLocation;

	if(m_pPlayerControllers[0])
		m_pPlayerControllers[0]->ProjectWorldLocationToScreen(pPlayer->GetPawn()->GetActorLocation(), screenLocation);

	int32 screenWidth = 0;
	int32 screenHeight = 0;
	pPlayer->GetViewportSize(screenWidth, screenHeight);

	const int32 screenX = (int32)screenLocation.X;

	const int32 minX{int32((1 - m_StartZoomingIn) * screenWidth)};
	const int32 maxX{int32(m_StartZoomingIn * screenWidth)};

	if(screenX >= minX && screenX < maxX)
	{
		float zoomSpeed{};
		if(screenX > screenWidth / 2)
		{
			zoomSpeed = (maxX - screenX) / float(maxX - screenWidth / 2);
			if(zoomSpeed < m_ZoomSpeed)
			{
				m_ZoomSpeed = zoomSpeed;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(m_ZoomSpeed));
			return true;
		}

		if(screenX < screenWidth / 2)
		{
			zoomSpeed = (screenX - minX) / float(screenWidth / 2 - minX);
			if(zoomSpeed < m_ZoomSpeed)
			{
				m_ZoomSpeed = zoomSpeed;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(m_ZoomSpeed));
			return true;
		}
	}
	return false;
}

void ACustomCameraActor::MoveCameraBack()
{
	FVector actorPos = m_pRenderTarget->GetActorLocation();

	if ((actorPos.X > m_MaxEndCamPos.X && actorPos.Z < m_MaxEndCamPos.Z))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "MoveBack");
		m_pRenderTarget->AddActorWorldOffset(FVector(-1, 0, 1) * (m_CamSpeed * m_ZoomSpeed), true);
	}
}

void ACustomCameraActor::MoveCameraForward()
{
	FVector actorPos = m_pRenderTarget->GetActorLocation();

	if ((actorPos.X < m_StartCamPos.X && actorPos.Z > m_StartCamPos.Z))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "MoveForward");
		m_pRenderTarget->AddActorWorldOffset(FVector(1, 0, -1) * (m_CamSpeed * m_ZoomSpeed), true);
	}

}

