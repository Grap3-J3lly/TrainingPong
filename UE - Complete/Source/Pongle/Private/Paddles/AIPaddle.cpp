// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddles/AIPaddle.h"

#include "Balls/SimpleBall.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PUBLIC LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// TODO: Need to implement a Max Speed of 5000
// TODO: Need to determine a viable Min Speed (1000?)
// TODO: Test Max Speed of 6000

// Constructor
AAIPaddle::AAIPaddle()
{
	PrimaryActorTick.bCanEverTick = true;
	if (MovementComponent != nullptr)
	{
		MovementComponent->UpdatedComponent = GetRootComponent();
	}
}

// Standard Functions
void AAIPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

// - - - Functions - - -
void AAIPaddle::SetGameBallReference(ASimpleBall* Ball)
{
	GameBall = Ball;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PROTECTED LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// - - - Functions - - -
void AAIPaddle::Move(float AxisValue)
{
	Super::Move(AxisValue);

	if (AxisValue != 0)
	{
		FVector Direction = FVector(0, AxisValue, 0);

		if ((AxisValue > 0 && MovementComponent->Velocity.Y < 0) || AxisValue < 0 && MovementComponent->Velocity.Y > 0)
		{
			/*if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, TEXT("Resetting Velocity"));*/
			MovementComponent->Velocity = FVector::ZeroVector;
		}
		
		MovementComponent->AddInputVector(Direction);
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PRIVATE LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

void AAIPaddle::HandleMovement()
{
	// If the ball is coming towards the AI Paddle
	if (GameBall != nullptr && GameBall->GetVelocity().X > 0)
	{
		float Y = ComputeBallYCoordinate(); //GameBall->GetActorLocation().Y;

		if (Y > GetActorLocation().Y)
		{
			/*if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Calling Move 1"));*/
			Move(1);
		}
		else if (Y < GetActorLocation().Y)
		{
			/*if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Calling Move -1"));*/
			Move(-1);
		}
		else
		{
			/*if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Calling Move 0"));*/
			Move(0);
		}
	}
	else
	{
		/*if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Calling Else Statement"));*/
		if (GetActorLocation().Y < 0)
		{
			Move(1);
		}
		else if (GetActorLocation().Y > 0)
		{
			Move(-1);
		}
		else
		{
			Move(0);
		}
	}
}

float AAIPaddle::ComputeBallYCoordinate() const
{
	float Y = 0;

	FVector PaddleLocation = GetActorLocation();
	FVector BallLocation = GameBall->GetActorLocation();
	FVector BallVelocity = GameBall->GetVelocity();

	float RateOfChange = (PaddleLocation.X - BallLocation.X) / BallVelocity.X;
	Y = (BallVelocity.Y * RateOfChange) + BallLocation.Y;

	return Y;
}