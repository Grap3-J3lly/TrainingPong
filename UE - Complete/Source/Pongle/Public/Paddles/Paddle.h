// Fill out your copyright notice in the Description page of Project Settings.

/*
* Credit to Oscar Alarcon for Paddle Setup. https://medium.com/@ViaCognita/atari-pong-clone-b14707bca3a5
* I utilized this tutorial to get an idea for how to set up physics components within Unreal Engine using C++. 
* I also thought his naming structure for the components makes a lot of sense and will be utilizing it or something similar in my projects going forward.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

// Forward Declarations
class UArrowComponent;
class UBoxComponent;
class UFloatingPawnMovement;

UCLASS()
class PONGLE_API APaddle : public APawn
{
	GENERATED_BODY()

public:	
	// Constructor
	APaddle();
	
	// Standard Functions
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Functions
	FVector GetVelocity() const;

protected:
	// UPROPERTIES
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* MovementComponent;

	// Variables
	float PaddleXValue;

	// Standard Functions
	virtual void BeginPlay() override;

	// UFUNCTIONS
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Functions
	virtual void Move(float AxisValue);

private:
	// UPROPERTIES
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* ForwardArrow;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualComponent;

	// Functions
	void SetupCollision();

};
