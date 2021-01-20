
#include "CharSelectorInd.h"
#include "Engine.h"
#include <string>
#include "Materials/MaterialInstanceDynamic.h"

ACharSelectorInd::ACharSelectorInd()
{
	PrimaryActorTick.bCanEverTick = true;
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	RootComponent = m_pMesh;
}

void ACharSelectorInd::BeginPlay()
{
	Super::BeginPlay();
}

void ACharSelectorInd::SetMaterial(UMaterialInstance* material)
{	
	m_pMesh->SetMaterial(0, material);
}

void ACharSelectorInd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_SwipeTimer -= DeltaTime;
	m_ButtonTimer -= DeltaTime;
}

void ACharSelectorInd::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &ACharSelectorInd::Select);
	
	PlayerInputComponent->BindAction("Activate Player", IE_Pressed, this, &ACharSelectorInd::BecomeActive);

	PlayerInputComponent->BindAxis("moveIndX", this, &ACharSelectorInd::MovePos);
}

void ACharSelectorInd::MovePos(float val)
{
	if(!m_Active)
		return;
	
	if(m_Selected)
		return;

	if(m_SwipeTimer > 0)
		return;

	if(val > 0.5f)
	{
		if(m_Pos < 3)
		{
			m_SwipeTimer = m_SwipeDelay;
			m_Pos++;
			NotifyGoRight();
		}
	}
	else if(val < -0.5f)
	{
		if(m_Pos > 0)
		{
			m_SwipeTimer = m_SwipeDelay;
			m_Pos--;
			NotifyGoLeft();
		}
	}
}

void ACharSelectorInd::Select()
{
	if(m_ButtonTimer > 0)
	return;

	if(IsAlreadySelected())
		return;

	if(!m_Active)
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

void ACharSelectorInd::BecomeActive()
{
	if(!m_Active)
	{
		m_Active = true;
		NotifyActive();
	}
}

bool ACharSelectorInd::IsAlreadySelected()
{
	TArray<AActor*> allIndicators;
	auto classToFind= ACharSelectorInd::StaticClass();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),classToFind,allIndicators);

	for(auto i : allIndicators)
	{
		auto indicator = Cast<ACharSelectorInd>(i);

		if(indicator == this)
			continue;
		
		if(indicator->GetPos() == m_Pos && indicator->IsSelected())
		{
			return true;
		}
	}
	return false;
}

