#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EndScreenPawn.generated.h"

UCLASS()
class AEndScreenPawn : public APawn
{
	GENERATED_BODY()

public:
	AEndScreenPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void Reset();
	void Quit();
};
