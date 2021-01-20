// Fill out your copyright notice in the Description page of Project Settings.


#include "CharSelectAnimatedPirate.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ACharSelectAnimatedPirate::ACharSelectAnimatedPirate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	SetRootComponent(m_pSkeletalMesh);
}

// Called when the game starts or when spawned
void ACharSelectAnimatedPirate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharSelectAnimatedPirate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

