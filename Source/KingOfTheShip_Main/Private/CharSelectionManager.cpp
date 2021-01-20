// Fill out your copyright notice in the Description page of Project Settings.


#include "CharSelectionManager.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "CharSelectorInd.h"
#include "Kismet/GameplayStatics.h"
#include "CharGameInstance.h"
#include "CharSelectAnimatedPirate.h"

// Sets default values
ACharSelectionManager::ACharSelectionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACharSelectionManager::AdvanceLevel()
{
	for(int i{}; i < m_CharSelectors.Num(); i++)
	{
		auto gameInstance = Cast<UCharGameInstance>(GetGameInstance());
		if(gameInstance)
		{
			gameInstance->m_SelectedCharacter.Push(Cast<ACharSelectorInd>(m_CharSelectors[i])->GetPos());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "GameInstance was nullptr");
		}
	}
	
	UGameplayStatics::OpenLevel(GetWorld(),FName("Main"));
}

// Called when the game starts or when spawned
void ACharSelectionManager::BeginPlay()
{
	Super::BeginPlay();
	
	for(int i{}; i < m_CharSelectors.Num(); i++)
	{
		Cast<ACharSelectorInd>(m_CharSelectors[i])->SetMaterial(m_Materials[i]);
	}
}

// Called every frame
void ACharSelectionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCharAnimations();
	PlacementIndicators();
	CheckCharactorsSelected();
}

void ACharSelectionManager::CheckCharactorsSelected()
{
	for(auto i : m_CharSelectors)
	{
		auto indicator = Cast<ACharSelectorInd>(i);
		if(!indicator->IsSelected())
		{
			return;
		}
	}
	for(int i{}; i < m_CharSelectors.Num(); i++)
	{
		auto gameInstance = Cast<UCharGameInstance>(GetGameInstance());
		if(gameInstance)
		{
			gameInstance->m_SelectedCharacter.Push(Cast<ACharSelectorInd>(m_CharSelectors[i])->GetPos());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "GameInstance was nullptr");
		}
	}
	
	UGameplayStatics::OpenLevel(GetWorld(),FName("Main"));
}

void ACharSelectionManager::PlacementIndicators()
{
	int indInPos[4]{};
	int currentIndInPos[4]{};
	float widthBetweenInd{20};

	// add up all the indicatorpositions
	for(auto i : m_CharSelectors)
	{
		if(i)
		{	
			ACharSelectorInd* indicator = Cast<ACharSelectorInd>(i);

			if(!indicator->IsActive())
				continue;
			
			auto pos = indicator->GetPos();

			indInPos[pos]++;
		}
	}

	// place the indicator depending on how many are in that position
	for(auto i : m_CharSelectors)
	{
		if(i)
		{
			ACharSelectorInd* indicator = Cast<ACharSelectorInd>(i);

			if(!indicator->IsActive())
				continue;
			
			auto pos = indicator->GetPos();
			
			indicator->m_pMesh->SetRelativeLocation(m_pPirates[pos]->GetTransform().GetLocation() + FVector(0, 0, 140)
				- FVector(widthBetweenInd / 2 * (indInPos[pos] - 1), 0, 0)
				+ FVector( widthBetweenInd * (currentIndInPos[pos] - 1), 0, 0));
			indicator->m_pMesh->SetRelativeRotation(m_pPirates[pos]->GetTransform().GetRotation() + FQuat(0,0,1, 90));

			currentIndInPos[pos]++;
		}
	}
}

void ACharSelectionManager::UpdateCharAnimations()
{
	for(auto i : m_CharSelectors)
	{
		auto indicator = Cast<ACharSelectorInd>(i);

		if(!indicator->IsActive())
			continue;

		auto pirate = Cast<ACharSelectAnimatedPirate>(m_pPirates[indicator->GetPos()]);
		
		if(indicator->IsSelected())
		{
			pirate->SetIsSelected(true);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::SanitizeFloat(float(indicator->GetPos())));
		}
		else
		{
			pirate->SetIsSelected(false);
		}
	}
}

