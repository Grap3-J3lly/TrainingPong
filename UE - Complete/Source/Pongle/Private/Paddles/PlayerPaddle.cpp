// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddles/PlayerPaddle.h"

#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PUBLIC LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Constructor
APlayerPaddle::APlayerPaddle()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Standard Functions
void APlayerPaddle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPaddle::ProcessMove);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerPaddle::ProcessInteract);
	}
}

UUserWidget* APlayerPaddle::GetHUD() const
{
	return HUD;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PROTECTED LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Standard Functions
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PongleMappingContext, 0);
		}
	}

	// Setup UI
	HUD = CreateWidget(GetWorld(), HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}

// Functions
void APlayerPaddle::ProcessMove(const FInputActionValue& Value)
{
	const float MovementDirection = Value.Get<float>();

	Move(MovementDirection);
}

void APlayerPaddle::ProcessInteract(const FInputActionValue& Value)
{
	FGenericPlatformMisc::RequestExit(false);
}

void APlayerPaddle::Move(float AxisValue)
{
	Super::Move(AxisValue);

	AddMovementInput(GetActorRightVector(), AxisValue);
}