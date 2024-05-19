// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Paddles/Paddle.h"
#include "InputActionValue.h"
#include "PlayerPaddle.generated.h"

// Forward Declarations
class UInputAction;
class UInputMappingContext;


UCLASS()
class PONGLE_API APlayerPaddle : public APaddle
{
	GENERATED_BODY()

public:	
	// Constructor
	APlayerPaddle();
	
	

	// Standard Functions
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Functions
	UUserWidget* GetHUD() const;

protected:
	// UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* PongleMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;
	UPROPERTY()
	UUserWidget* HUD;
	
	// Standard Functions
	virtual void BeginPlay() override;
	
	// Functions
	void ProcessMove(const FInputActionValue& Value);
	void ProcessInteract(const FInputActionValue& Value);
	
	virtual void Move(float AxisValue) override;
};
