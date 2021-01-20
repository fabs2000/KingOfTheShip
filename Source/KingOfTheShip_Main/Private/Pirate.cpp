#include "Pirate.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Math/RandomStream.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ChestManager.h"
#include "Rum.h"
#include "PowerShot.h"
#include "SpeedBoost.h"
#include "Animation/AnimSequence.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"


APirate::APirate()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pCapsule = FindComponentByClass<UCapsuleComponent>();

	m_Effect = Effect::None;
}

void APirate::BeginPlay()
{
	Super::BeginPlay();

	m_pSelfMovementComp = this->FindComponentByClass<UCharacterMovementComponent>();

	m_pWeapon = this->FindComponentByClass<UWeapon>();
	m_pChestManager = Cast<AChestManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AChestManager::StaticClass()));
	//m_NotificationManager = Cast<ANotificationsManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ANotificationsManager::StaticClass()));

	//CHECKS FOR NULLPTR
	if (!m_pChestManager)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "chestManager = nullptr");
	}
	if (!m_pWeapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Weapon = nullptr");
	}

	m_pCapsule->OnComponentBeginOverlap.AddDynamic(this, &APirate::OnOverlapBegin);
	
	m_RespawnRef = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));
}

void APirate::MoveForward(float value)
{
	if (!m_IsInWater)
		m_MoveDirection.Y = value;
}

void APirate::MoveRight(float value)
{
	if (!m_IsInWater)
		m_MoveDirection.X = value;
}

void APirate::LookRight(float value)
{
	m_LookDirection.X = value;
}

void APirate::LookForward(float value)
{
	m_LookDirection.Y = value;
}

// Called every frame
void APirate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_DashTimer > 0.f)
		m_DashTimer -= DeltaTime;

	if (m_IsInWater)
	{
		if (m_DrownTimer >= 0.f)
			m_DrownTimer -= DeltaTime;
	}
	if (m_IsInWater)
		HandleRecovery();

	if (m_IsSlowed)
		HandleSlowed(DeltaTime);

	if (m_IsDead && m_LifePoints > 0)
	{
		m_LifePoints--;
		if (m_LifePoints == 0)
		{
			m_ToBeSubtracted = true;
			SetActorTickEnabled(false);
		}
		else
		{
			m_RespawnRef->SetPlayerPosition(this);
			m_pSelfMovementComp->SetMovementMode(EMovementMode::MOVE_Falling);
			m_IsDead = false;
		}
	}

	auto pos = GetActorLocation();

	if (pos.Z <= -100.f || pos.Z >= 3000.f || (pos.X >= 3000.f || pos.X <= -3000.f))
	{
		m_IsDead = true;
		m_pSelfMovementComp->SetMovementMode(EMovementMode::MOVE_None);
	}

	HandleMovement();

	m_EffectTimer -= DeltaTime;

	if (m_EffectTimer <= 0 && m_Effect != Effect::None)
		ResetEffects();
}

// Called to bind functionality to input
void APirate::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// Bind dash event
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APirate::Dash);

	// Bind fire event
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APirate::Shoot);

	//Bind recovering event
	PlayerInputComponent->BindAction("Recover", IE_Pressed, this, &APirate::Recover);

	// Bind interaction
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APirate::Interact);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APirate::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APirate::MoveRight);

	// Bind looking events
	PlayerInputComponent->BindAxis("LookForward", this, &APirate::LookForward);
	PlayerInputComponent->BindAxis("LookRight", this, &APirate::LookRight);
}

void APirate::Shoot()
{
	if (!m_IsInWater)
		m_pWeapon->SetShootingTrue();
}

void APirate::Dash()
{
	// Check if the dash is not on cd
	if (!m_IsInWater)
	{
		if (m_DashTimer >= 0.f)
			return;

		NotifyDash();

		FVector actorForward = FVector(GetActorForwardVector().X, GetActorForwardVector().Y, m_DashUpOffset);

		actorForward.Normalize();
		
		if (m_pSelfMovementComp->IsFalling())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "It Detects the condition");
			m_pSelfMovementComp->Launch(actorForward * m_FlyingDashForce);
		}
		else
		{
			m_pSelfMovementComp->Launch(actorForward * m_DashForce);
		}
		m_pSelfMovementComp->HandlePendingLaunch();

		m_DashTimer += 1.0f / m_DashRate;
	}
}

void APirate::Interact()
{
	for (AActor* chest : m_pChestManager->GetChests())
	{
		if (FVector::Distance(chest->GetTransform().GetLocation(), GetTransform().GetLocation()) < m_InteractionRange)
		{
			//(chest->GetTransform().GetLocation() - GetTransform().GetLocation()).Size()
			Cast<AChest>(chest)->OpenChest();
		}
	}
}

void APirate::Recover()
{
	if (m_IsInWater)
	{
		m_MashingCounter++;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			//FString::FromInt(m_MashingCounter));
		NotifyRecover();
	}
}

void APirate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr)
		return;

	// if there is already an active effect reset the effect
	ResetEffects();

	if (Cast<APickUpBase>(OtherActor))
	{
		if (Cast<ARum>(OtherActor))
		{
			m_Effect = Effect::Drunk;
		}
		else if (Cast<ASpeedBoost>(OtherActor))
		{
			m_Effect = Effect::SpeedBoost;
		}
		else if (Cast<APowerShot>(OtherActor))
		{
			m_Effect = Effect::PowerShot;
		}
		OtherActor->Destroy();
	}

	// DestroyActiveEffectAnimation
	if (m_pActiveEffect)
		m_pActiveEffect->DestroyInstance();

	// Apply effect
	switch (m_Effect)
	{
	case Effect::Drunk:
		m_pWeapon->SetStrongerBlast(true);
		break;
	case Effect::SpeedBoost:
		GetCharacterMovement()->MaxWalkSpeed *= m_MovementSpeedMultiplier;
		break;
	case Effect::PowerShot:
		m_pWeapon->SetPowerShot(true);
		break;
	case Effect::None:
		break;
	}
	m_EffectTimer = m_EffectDuration;
}

void APirate::HandleRecovery()
{
	if (m_DrownTimer <= 0.f)
	{
		m_CounterUntilDrown++;

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			//FString::FromInt(m_CounterUntilDrown));

		m_DrownTimer += 1.0f / m_DrownRate;
	}

	if (m_MashingCounter == m_MaxTimeUntilDeath)
	{
		m_MashingCounter = 0;
		m_CounterUntilDrown = 0;

		//Movement Component Output
		m_pSelfMovementComp->GravityScale = 1.f;
		m_pSelfMovementComp->SetMovementMode(EMovementMode::MOVE_Flying);

		FVector launchForce = FVector(0, 0, 1) * 1250;

		auto pos = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 150.f);
		SetActorLocation(pos);

		m_pSelfMovementComp->Launch(launchForce);

		m_IsInWater = false;

	}
	else if (m_CounterUntilDrown == m_MaxTimeUntilDeath)
	{
		m_IsDead = true;

		m_MashingCounter = 0;
		m_CounterUntilDrown = 0;

		m_pSelfMovementComp->GravityScale = 1.f;
		m_pSelfMovementComp->SetMovementMode(EMovementMode::MOVE_Falling);

		m_IsInWater = false;
	}
}

void APirate::ResetEffects()
{
	// Reset effect
	switch (m_Effect)
	{
	case Effect::Drunk:
		m_pWeapon->SetStrongerBlast(false);
		break;
	case Effect::SpeedBoost:
		GetCharacterMovement()->MaxWalkSpeed /= m_MovementSpeedMultiplier;
		break;
	case Effect::PowerShot:
		m_pWeapon->SetPowerShot(false);
		break;
	case Effect::None:
		break;
	}

	m_Effect = Effect::None;
}

void APirate::HandleMovement()
{
	if (m_LookDirection != FVector2D::ZeroVector)
	{
		m_LookDirection.Normalize();
		float angle = atan2(m_LookDirection.X, -m_LookDirection.Y);
		angle *= 360;
		angle /= 2 * PI;
		Controller->SetControlRotation(FRotator{ 0, angle, 0 });
		SetActorRotation(Controller->GetControlRotation());
	}

	if (m_MoveDirection != FVector2D::ZeroVector)
	{
		m_MoveDirection.Normalize();
		if (m_Effect == Effect::Drunk)
		{
			AddMovementInput(FVector(-m_MoveDirection, 0));
		}
		else
		{
			AddMovementInput(FVector(m_MoveDirection, 0));

		}

		FVector offsettedActorPos = GetMesh()->GetComponentLocation() + GetActorForwardVector() * m_SmokeOffset;

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_pWalkEffect, offsettedActorPos);
	}
}

void APirate::HandleSlowed(float dt)
{
	m_SlowedTimer += dt;

	if (m_SlowedTimer >= m_MaxSlowTime)
	{
		m_IsSlowed = false;
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Called reset slowed");
		m_pSelfMovementComp->MaxAcceleration = m_NormalAcceleration;
		m_SlowedTimer = 0.f;
	}
}

void APirate::Landed(const FHitResult& hit)
{
	Super::Landed(hit);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_pFallEffect, FVector(hit.Location.X, hit.Location.Y, hit.Location.Z - m_FallEffectOffset));
}

void APirate::SetIsInWater(bool isInWater)
{
	m_IsInWater = isInWater;
	ResetEffects();
}

void APirate::SetIsSlowed(bool isSlowed)
{
	m_IsSlowed = isSlowed;

	m_NormalAcceleration = m_pSelfMovementComp->MaxAcceleration;
	m_pSelfMovementComp->MaxAcceleration = m_SlowedAcceleration;

	ResetEffects();
}