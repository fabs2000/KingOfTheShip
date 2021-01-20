// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Chest.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUpManager.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPowerUpManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerUpManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AChest> m_ToSpawn;
	
	UPROPERTY(EditAnyWhere)
	float m_SpawnRate = 20.f;

	UPROPERTY(EditAnyWhere)
	int m_MaxChests = 2;

	void SpawnPowerUp();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> m_Chests;

	float m_SpawnTimer;

};
