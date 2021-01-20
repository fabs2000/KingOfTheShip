#include "StunBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Pirate.h"
#include "Engine/Engine.h"

AStunBarrel::AStunBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AStunBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	//This overrides tab in BP and doesn't show you the full thing
	//m_pBarrelMesh->SetSimulatePhysics(true);

	m_pBarrelMesh = Cast<UStaticMeshComponent>(RootComponent);

	if (m_pBarrelMesh)
	{
		m_pBarrelMesh->OnComponentHit.AddDynamic(
			this, &AStunBarrel::OnHit);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Barrel mesh nullptr");
	}
}

void AStunBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (this->GetActorLocation().Z < 0.f)
	{
		this->Destroy();
	}
}

void AStunBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "ItWorks");

	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor->ActorHasTag("Pirate"))
		{
			APirate* pPirate = Cast<APirate>(OtherActor);

			if (pPirate != nullptr)
			{
				pPirate->SetIsSlowed(true);

				Destroy();
			}
		}
	}
}

