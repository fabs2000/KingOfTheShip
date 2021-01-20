
#include "EndScreenPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine.h"

AEndScreenPawn::AEndScreenPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEndScreenPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEndScreenPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndScreenPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Reset", IE_Pressed, this, &AEndScreenPawn::Reset);

	PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &AEndScreenPawn::Quit);

}

void AEndScreenPawn::Reset()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("CharacterSelection"));
}

void AEndScreenPawn::Quit()
{
	auto pC = UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0);

	UKismetSystemLibrary::QuitGame(GetWorld(), pC, EQuitPreference::Quit, false);
}