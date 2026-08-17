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

	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
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

void AMCOCharacter_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComp->BindAction(InputAction_Jump, ETriggerEvent::Triggered, this,
	                              &AMCOCharacter_Player::HandleActionJump);

	EnhancedInputComp->BindAction(InputAction_Look, ETriggerEvent::Triggered, this,
	                              &AMCOCharacter_Player::HandleActionLook);

	EnhancedInputComp->BindAction(InputAction_Move, ETriggerEvent::Triggered, this,
	                              &AMCOCharacter_Player::HandleActionMove);
}

void AMCOCharacter_Player::HandleActionJump()
{
	UE_LOG(LogTemp, Warning, TEXT("Handle Action Jump"));
	Jump();
}

void AMCOCharacter_Player::HandleActionLook(const FInputActionValue& InputValue)
{
	// bool
	// vector 2
	// vector 3
	FVector2D InputValue_2D = InputValue.Get<FVector2D>();


	AddControllerPitchInput(InputValue_2D.Y);
	AddControllerYawInput(InputValue_2D.X);
}

void AMCOCharacter_Player::HandleActionMove(const FInputActionValue& InputValue)
{
	FVector2D InputValue_2D = InputValue.Get<FVector2D>();
	
	if (bClampMovementInput)
	{
		InputValue_2D = InputValue.Get<FVector2D>().GetClampedToMaxSize(1.f);
	}
	
	
	double MovementLength = InputValue_2D.Length();
	UE_LOG(LogTemp, Warning, TEXT("Move Length: %f"), MovementLength);

	// UE_LOG(
	// 	LogTemp, Warning, TEXT("X: %f, Y: %f"),
	// 	InputValue_2D.X,
	// 	InputValue_2D.Y
	// );
}
