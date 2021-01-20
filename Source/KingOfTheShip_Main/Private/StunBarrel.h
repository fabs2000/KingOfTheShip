#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StunBarrel.generated.h"

UCLASS()
class AStunBarrel : public AActor
{
	GENERATED_BODY()

public:
	AStunBarrel();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;

private:

	UStaticMeshComponent* m_pBarrelMesh;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);



};
