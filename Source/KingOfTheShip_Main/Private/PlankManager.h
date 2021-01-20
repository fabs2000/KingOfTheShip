#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Plank.h"
#include "KingOfTheShip_MainGameModeBase.h"
#include "PlankManager.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlankManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlankManager();

	UPROPERTY(EditAnywhere)
		float m_EventCooldownTime = 10.f;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
	void EnableDisableSpawner();

private:
	AKingOfTheShip_MainGameModeBase* m_pGameModeRef;
	FTimerHandle m_TimerHandle;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> m_Planks;

	UPROPERTY(EditAnyWhere)
	float DestroyRate = 0.8f;
	float m_DestroyTimer;

	void DestoryPlank();
};
