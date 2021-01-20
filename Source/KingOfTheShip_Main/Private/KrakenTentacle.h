#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "Ship.h"
#include "Rocking.h"
#include "KrakenTentacle.generated.h"

UCLASS()
class AKrakenTentacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AKrakenTentacle();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* m_pBody;

	UPROPERTY(EditAnywhere)
	FVector m_RaycastAreaDimensions;

	UPROPERTY(EditAnywhere)
	float m_RayCastLength;

	UPROPERTY(EditAnywhere)
	float m_LaunchForce = 2500.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShake> Shake;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LaunchObjects();

	void SetRayCastOrigin(ATargetPoint* pTarg) { m_pRayCastOrigin = pTarg; }

private:

	ATargetPoint* m_pRayCastOrigin;

	AShip* m_pShipRef;
};
