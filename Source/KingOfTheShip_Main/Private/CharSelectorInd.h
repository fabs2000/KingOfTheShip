#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharSelectorInd.generated.h"

UCLASS()
class ACharSelectorInd : public APawn
{
	GENERATED_BODY()

public:	
	ACharSelectorInd();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* m_pMesh;

	void SetMaterial(class UMaterialInstance* material);

	int GetPos() const { return m_Pos; }
	bool IsSelected() const { return m_Selected; }
	bool IsActive() const { return m_Active; }
	
	UFUNCTION(BlueprintImplementableEvent)
	void NotifyActive();
	UFUNCTION(BlueprintImplementableEvent)
	void NotifyGoRight();
	UFUNCTION(BlueprintImplementableEvent)
	void NotifyGoLeft();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MovePos(float val);
	void Select();
	void BecomeActive();
	bool IsAlreadySelected();

	int m_Pos = 0;
	bool m_Active = false;
	bool m_Selected = false;
	
	float m_SwipeDelay = 0.3f;
	float m_SwipeTimer;
	float m_ButtonDelay = 0.6f;
	float m_ButtonTimer;

};
