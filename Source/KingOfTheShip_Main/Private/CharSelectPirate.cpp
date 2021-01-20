// Fill out your copyright notice in the Description page of Project Settings.


#include "CharSelectPirate.h"

// Sets default values
ACharSelectPirate::ACharSelectPirate()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharSelectPirate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharSelectPirate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetVelocity().Set(0,0,0);
}

// Called to bind functionality to input
void ACharSelectPirate::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

