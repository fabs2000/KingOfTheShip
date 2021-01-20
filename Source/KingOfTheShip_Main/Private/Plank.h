// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Plank.generated.h"

UENUM(BlueprintType)
enum class PlankState : uint8
{
	Alive,
	Warn,
	CountdownDisabled,
	Disabled,
	CountdownAlive
};

UCLASS()
class APlank : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlank();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	UStaticMeshComponent* Base;

	UPROPERTY(EditAnywhere, Category = "Timers")
	float WarningTime = 2.f;

	UPROPERTY(EditAnywhere, Category = "Timers")
	float DisabledTime = 15.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	PlankState m_PlankState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrepareDisable();
	void DisableActor();
	void EnableActor();

	bool IsActive;

private:
	float m_WarningTimer;
	float m_DisabledTimer;
	
};
