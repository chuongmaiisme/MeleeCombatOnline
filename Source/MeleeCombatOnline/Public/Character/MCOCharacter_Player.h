// Gary

#pragma once

#include "CoreMinimal.h"
#include "Character/MCOCharacter.h"
#include "MCOCharacter_Player.generated.h"

class UCameraComponent;
/**
 * 
 */
UCLASS()
class MELEECOMBATONLINE_API AMCOCharacter_Player : public AMCOCharacter
{
	GENERATED_BODY()
	
	UPROPERTY()
	UCameraComponent* CameraComp;
};
