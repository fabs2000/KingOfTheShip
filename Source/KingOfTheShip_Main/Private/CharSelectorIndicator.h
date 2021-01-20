// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharSelectorIndicator.generated.h"

UCLASS()
class ACharSelectorIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharSelectorIndicator();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	void SetPlayerController(APlayerController* player) { m_pPlayer = player; }

	void SetMaterial(class UMaterialInstance* material);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int m_Pos = 0;
	bool m_Selected = false;
	APlayerController* m_pPlayer;
	
	float m_SwipeDelay = 0.3f;
	float m_SwipeTimer;
	float m_ButtonDelay = 0.6f;
	float m_ButtonTimer;
};
