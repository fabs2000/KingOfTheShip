// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PowerShotProjectile.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Components/ArrowComponent.h"
#include "Weapon.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon();

	UPROPERTY(EditAnywhere)
		float m_RayLength = 150;

	UPROPERTY(EditAnywhere)
		float m_ImpulseForce = 500;

	UPROPERTY(EditAnywhere)
		float m_FireRate = 1.f;

	UPROPERTY(EditAnywhere)
		FVector2D m_ShotWidthHeight = FVector2D(80, 80);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShootingTrue();
	void SetStrongerBlast(bool isStrongerBlast) { m_IsStrongerBlast = isStrongerBlast;}
	void SetPowerShot(bool isPowerShot) { m_IsPowerShot = isPowerShot; }

private:
	//Refs to Character
	UCharacterMovementComponent* m_pSelfMovementComp;
	AActor* m_pOwner;
	
	//Shooting
	FCollisionShape m_BoxCollision;
	FRandomStream m_Random;

	TSubclassOf<APowerShotProjectile> m_PowerShot;

	float m_FireTimer = 0.f;
	bool m_TriggerPulled = false;
	bool m_IsStrongerBlast = false;
	bool m_IsPowerShot = false;
	float m_PowerShotOffset = 100.f;

	UFUNCTION(BlueprintCallable, Category = "CanShoot")
	bool CanShoot();

	void Shoot();
	void ShootCannonball();

	UFUNCTION(BlueprintCallable)
	float GetShootCdPercentage() const { return (1 - (m_FireTimer / (1 / m_FireRate)));}
	
	FVector m_ShotOffset = FVector(65.f, -50.f, -30.f);
};
