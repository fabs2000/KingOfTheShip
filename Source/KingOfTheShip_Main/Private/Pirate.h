#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "Runtime/Engine/Public/WorldCollision.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Ship.h"
#include "Pirate.generated.h"


UENUM(BlueprintType)
enum class Effect : uint8
{
	None,
	Drunk,
	SpeedBoost,
	PowerShot
};

UENUM(BlueprintType)
enum class PirateType : uint8
{
	Captn,
	Parry,
	Sharky,
	Shrimp
};

UCLASS()
class APirate : public ACharacter
{
	GENERATED_BODY()

public:
	APirate();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int m_LifePoints = 3;

	UPROPERTY(EditAnywhere)
		float m_DashForce = 1000;

	UPROPERTY(EditAnywhere)
		float m_FlyingDashForce = 300.f;

	UPROPERTY(EditAnywhere)
		float m_DashRate = 0.5f;

	UPROPERTY(EditAnywhere)
		float m_DashUpOffset = 0.2f;

	UPROPERTY(EditAnywhere)
		float m_InteractionRange = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		float m_BaseTurnRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWeapon* m_pWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enum)
		Effect m_Effect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enum)
		PirateType m_PirateType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EffectTime)
		float m_EffectDuration = 10.f;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* m_pWalkEffect;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* m_pFallEffect;

	UPROPERTY(BlueprintReadWrite)
		UNiagaraComponent* m_pActiveEffect;

	UFUNCTION(BlueprintImplementableEvent)
		void NotifyDash();

	UFUNCTION(BlueprintImplementableEvent)
		void NotifyRecover();

	UFUNCTION(BlueprintImplementableEvent)
		void NotifyShoot();

	UFUNCTION(BlueprintImplementableEvent)
		void NotifyPowerShot();

	UPROPERTY(EditAnywhere)
		int m_MaxTimeUntilDeath = 15;

	UPROPERTY(EditAnywhere)
		float m_DrownRate = 0.5f;

	UPROPERTY(EditAnywhere)
		float m_MaxSlowTime = 2.f;

	UPROPERTY(EditAnywhere)
		float m_SlowedAcceleration = 100.f;

	UPROPERTY(EditAnywhere)
		int m_MaxRecoveryPoints = 3;

protected:
	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& hit) override;

	// Movement
	void MoveForward(float value);
	void MoveRight(float value);

	//Looking
	void LookRight(float value);
	void LookForward(float value);


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	bool m_IsInWater = false;

	void SetIsInWater(bool isInWater);
	void SetIsSlowed(bool isSlowed);

	bool GetIsToBeSubtracted() { return m_ToBeSubtracted; }
	void SetIsToBeSubstracted(bool isOut) { m_ToBeSubtracted = isOut; }
	
private:

	//Ship
	AShip* m_RespawnRef;

	//State m_PlayerState;
	UCapsuleComponent* m_pCapsule;

	////Notification system
	//class ANotificationsManager* m_NotificationManager = nullptr;

	//--Movement--//
	UCharacterMovementComponent* m_pSelfMovementComp;
	void HandleMovement();
	float m_DashTimer = 1.f;
	FVector2D m_LookDirection;
	FVector2D m_MoveDirection;
	float m_SmokeOffset = 10.f;

	//--PickUp Interactions--//
	// ChestManagerRef
	class AChestManager* m_pChestManager;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//--ACTIONS--//
	UFUNCTION(BlueprintCallable, Category = "SetShootTrue")
	void Shoot();
	void Dash();
	void Interact();

	//Recovering
	void Recover();
	void HandleRecovery();
	
	int m_MashingCounter = 0;
	int m_CounterUntilDrown = 0;

	float m_DrownTimer = 0.f;

	//Slowed 
	void HandleSlowed(float dt);
	float m_SlowedTimer = 0.f;
	float m_NormalAcceleration;

	//States TODO: Make into enum
	bool m_IsSlowed = false;
	bool m_IsDead = false;
	bool m_ToBeSubtracted = false;

	// Effect variables
	float m_EffectTimer;
	float m_MovementSpeedMultiplier = 2;
	float m_FallEffectOffset = 40.f;
	void ResetEffects();

	//HUD
	UFUNCTION(BlueprintCallable)
	float GetDashCdPercentage() const { return (1 - (m_DashTimer / (1 / m_DashRate))); }
	UFUNCTION(BlueprintCallable)
	float GetDrownPercentage() const { return float(m_CounterUntilDrown) / m_MaxTimeUntilDeath; }
	UFUNCTION(BlueprintCallable)
	float GetRecoverPercentage() const { return float(m_MashingCounter) / m_MaxTimeUntilDeath; }
};
