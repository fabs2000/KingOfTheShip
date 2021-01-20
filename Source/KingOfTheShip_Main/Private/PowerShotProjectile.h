// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PowerShotProjectile.generated.h"

UCLASS()
class APowerShotProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerShotProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		UProjectileMovementComponent* m_pProjMovement;

	UPROPERTY(EditAnywhere)
		float m_ShotStrength = 1500.f;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_pStaticMesh;

	//UPROPERTY(EditAnywhere)
	//	USphereComponent* m_pSphereCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void LaunchProjectile(const FVector& direction);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	bool m_IsLaunching;
	FVector m_ShotDirection;
};
