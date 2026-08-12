// Gary


#include "Character/MCOCharacter_Player.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMCOCharacter_Player::AMCOCharacter_Player()
{
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(GetRootComponent());
}

void AMCOCharacter_Player::PawnClientRestart()
{
	Super::PawnClientRestart();
	// Clients: Local Player
	// Local Player -> Player Controller -> Character
	// Add IMC by Local Player


	UE_LOG(LogTemp, Warning, TEXT("Player Controller possesses character"));

	AddMappingContext();
}

void AMCOCharacter_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComp->BindAction(InputAction_Jump, ETriggerEvent::Triggered, this, &AMCOCharacter_Player::HandleActionJump);
}

void AMCOCharacter_Player::AddMappingContext()
{
	APlayerController* MyPlayerController = GetController<APlayerController>();

	if (MyPlayerController == nullptr)
	{
		return;
	}

	ULocalPlayer* MyLocalPlayer = MyPlayerController->GetLocalPlayer();

	if (MyLocalPlayer == nullptr)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem =
		MyLocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();


	if (EnhancedInputSubsystem == nullptr)
	{
		return;
	}

	// Main Logic
	EnhancedInputSubsystem->RemoveMappingContext(IMC_Default);
	EnhancedInputSubsystem->AddMappingContext(IMC_Default, 0);
}

void AMCOCharacter_Player::HandleActionJump()
{
	UE_LOG(LogTemp, Warning, TEXT("Handle Action Jump"));
	Jump();
}
