// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Rocking.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class URocking : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URocking();
	
	AActor* m_pRoot;

	UPROPERTY(EditAnywhere)
	float AmplitudeRotation = 7.f;

	UPROPERTY(EditAnywhere)
	float AmplitudeTranslation = 7.f;

	UPROPERTY(EditAnywhere)
	float m_Period = 5;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetSpeed(float speed) { m_Speed = speed; } 

private:
	FVector m_StartPos;

	float m_Speed;
	float m_AccumulatedTime;
};