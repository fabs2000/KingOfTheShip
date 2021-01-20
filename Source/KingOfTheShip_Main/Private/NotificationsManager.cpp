// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationsManager.h"

// Sets default values
ANotificationsManager::ANotificationsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANotificationsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANotificationsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

