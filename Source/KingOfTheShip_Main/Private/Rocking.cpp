// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocking.h"
#include "GameFramework/Actor.h"
#include <string>
#include "Engine/Engine.h"

URocking::URocking()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URocking::BeginPlay()
{
	Super::BeginPlay();
	m_pRoot = GetOwner();
	m_StartPos = m_pRoot->GetActorLocation();
	m_Speed = 1;
	//this->SetComponentTickInterval(0.01f);
}


// Called every frame
void URocking::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float time{DeltaTime * m_Speed};

	m_AccumulatedTime += time;
	
	const float B = (m_AccumulatedTime / m_Period) * 2 * PI;
	
	const float rotation{ AmplitudeRotation * float(sin(B)) };
	const float translation{ AmplitudeTranslation * float(cos(B)) };
	
	if(m_pRoot)
	{
		m_pRoot->SetActorRelativeLocation(m_StartPos + FVector(0.f, 0.f, translation));
		m_pRoot->SetActorRotation(FRotator{ rotation, 0.f, 0.f });
	}
}