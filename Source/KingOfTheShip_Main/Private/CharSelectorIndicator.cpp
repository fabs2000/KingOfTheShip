// Fill out your copyright notice in the Description page of Project Settings.


#include "CharSelectorIndicator.h"
#include "Engine.h"
#include <string>
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ACharSelectorIndicator::ACharSelectorIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
}

void ACharSelectorIndicator::SetMaterial(UMaterialInstance* material)
{	
	mesh->SetMaterial(0, material);
}

// Called when the game starts or when spawned
void ACharSelectorIndicator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharSelectorIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!m_pPlayer)
		return;

	m_SwipeTimer -= DeltaTime;
	m_ButtonTimer -= DeltaTime;
	
	if(m_pPlayer->GetInputAnalogKeyState(EKeys::Gamepad_FaceButton_Left)  >= 0.99f)
	{
		if(m_ButtonTimer > 0)
			return;
		
		m_ButtonTimer = m_ButtonDelay;
		
		if(m_Selected == false)
		{
			m_Selected = true;
			return;
		}
		else
		{
			m_Selected = false;
		}
	}

	if(m_Selected)
		return;

	if(m_SwipeTimer > 0)
		return;

	float xVal{};
	float yVal{};
	
	m_pPlayer->GetInputAnalogStickState(EControllerAnalogStick::CAS_LeftStick, xVal, yVal);

	if(xVal > 0.5f)
	{
		if(m_Pos < 3)
		{
			m_SwipeTimer = m_SwipeDelay;
			m_Pos++;
		}
	}
	else if(xVal < -0.5f)
	{
		if(m_Pos > 0)
		{
			m_SwipeTimer = m_SwipeDelay;
			m_Pos--;
		}
	}
}

