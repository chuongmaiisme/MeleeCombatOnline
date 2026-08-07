// Gary

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCOCharacter.generated.h"

UCLASS()
class MELEECOMBATONLINE_API AMCOCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCOCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
