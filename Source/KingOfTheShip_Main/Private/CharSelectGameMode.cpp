// Fill out your copyright notice in the Description page of Project Settings.


#include "CharSelectGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ACharSelectGameMode::ACharSelectGameMode()
{
}

void ACharSelectGameMode::BeginPlay()
{
	for (int i{}; i < m_PlayerCount; i++)
	{
		UGameplayStatics::CreatePlayer(GetWorld(), i);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "player made");
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "beginplay called");
}
