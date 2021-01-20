// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "TimerManager.h"
#include "Engine.h"

AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AShip::BeginPlay()
{
	Super::BeginPlay();
	
	m_RockingTimer = -1;
	m_pRockingComp = FindComponentByClass<URocking>();
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_RockingTimer >= 0)
	{
		m_RockingTimer -= DeltaTime;

		float newSpeed = FMath::Lerp(1.f, m_RockMultiplier,(m_RockingTimer / m_TiltTime));
		m_pRockingComp->SetSpeed(newSpeed);

		//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString::SanitizeFloat(newSpeed));
	}
	else
	{
		m_pRockingComp->SetSpeed(1);
	}
}

void AShip::RockFast()
{
	//m_RockingTimer += dt;
	//m_pRockingComp->Period += m_PeriodBlendFactor;
	m_RockingTimer = m_TiltTime;

	//if (m_pRockingComp->Period >= m_pRockingComp->m_MaxPeriodValue)
	//{
	//	m_IsFastRotation = true;
	//	m_IsSlapped = false;
	//	//m_pRockingComp->Period = 4.f;
	//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Called reset Period");
	//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::SanitizeFloat(m_RockingTimer));
	//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::SanitizeFloat(m_pRockingComp->Period));
	//}
}

void AShip::SetPlayerPosition(AActor* pPlayer)
{
	int64 rndSpawnID = FMath::RandRange(0, 1);

	pPlayer->SetActorLocation(m_RespawnPoints[rndSpawnID]->GetActorLocation());
}

