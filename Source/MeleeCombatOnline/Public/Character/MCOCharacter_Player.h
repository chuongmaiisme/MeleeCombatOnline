// Gary

#pragma once

#include "CoreMinimal.h"
#include "Character/MCOCharacter.h"
#include "MCOCharacter_Player.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class MELEECOMBATONLINE_API AMCOCharacter_Player : public AMCOCharacter
{
	GENERATED_BODY()

public:
	AMCOCharacter_Player();

	virtual void PawnClientRestart() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: // Method
	void AddMappingContext();
	void HandleActionJump();

private: // Property
	UPROPERTY(visibleDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	// TObjectPtr<UInputMappingContext> IMC_Default;

	// Edit
	UPROPERTY(EditDefaultsOnly, Category="MCO Settings | Input")
	TObjectPtr<UInputMappingContext> IMC_Default;

	UPROPERTY(EditDefaultsOnly, Category="MCO Settings | Input")
	TObjectPtr<UInputAction> InputAction_Jump;
};
