// Fill out your copyright notice in the Description page of Project Settings.


#include "Plank.h"
#include "Components/DecalComponent.h"

// Sets default values
APlank::APlank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Base = CreateDefaultSubobject<UStaticMeshComponent>("Base");
	RootComponent = Base;
}

// Called when the game starts or when spawned
void APlank::BeginPlay()
{
	Super::BeginPlay();
	IsActive = true;
	m_PlankState = PlankState::Alive;
	m_WarningTimer = WarningTime;
	m_DisabledTimer = DisabledTime;
}

// Called every frame
void APlank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch(m_PlankState)
	{
	case PlankState::Alive:
		break;
	case PlankState::Warn:
		m_PlankState = PlankState::CountdownDisabled;
		break;
	case PlankState::CountdownDisabled:
		if (m_WarningTimer > 0.f)
		{
			m_WarningTimer -= DeltaTime;
		}
		else
		{
			m_WarningTimer = WarningTime;
			m_PlankState = PlankState::Disabled;
		}
		break;
	case PlankState::Disabled:
		DisableActor();
		m_PlankState = PlankState::CountdownAlive;
		break;
	case PlankState::CountdownAlive:
		if (m_DisabledTimer > 0.f)
		{
			m_DisabledTimer -= DeltaTime;
		}
		else
		{
			EnableActor();
		}
		break;
	}
}

void APlank::PrepareDisable()
{
	m_PlankState = PlankState::Warn;
	IsActive = false;
}

void APlank::DisableActor()
{
	Base->SetVisibility(false);
	Base->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APlank::EnableActor()
{
	Base->SetVisibility(true);
	Base->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	IsActive = true;
	m_PlankState = PlankState::Alive;
	m_DisabledTimer = DisabledTime;
}

