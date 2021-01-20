// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerShot.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Math/RandomStream.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"


// Sets default values
APowerShot::APowerShot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APowerShot::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APowerShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

