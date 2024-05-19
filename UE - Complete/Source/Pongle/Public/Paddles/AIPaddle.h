// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Paddles/Paddle.h"
#include "AIPaddle.generated.h"

// Forward Declarations
class ASimpleBall;

UCLASS()
class PONGLE_API AAIPaddle : public APaddle
{
	GENERATED_BODY()
	
public:
	AAIPaddle();

	// Standard Functions
	virtual void Tick(float DeltaTime) override;

	// Functions
	void SetGameBallReference(ASimpleBall* Ball);

protected:
	// Functions
	virtual void Move(float AxisValue) override;

private:	
	// Variables
	ASimpleBall* GameBall;

	// Functions
	void HandleMovement();
	float ComputeBallYCoordinate() const;
};
