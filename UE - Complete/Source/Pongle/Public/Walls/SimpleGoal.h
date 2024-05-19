// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleGoal.generated.h"

// Forward Declarations
class UBoxComponent;

UCLASS()
class PONGLE_API ASimpleGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// - - - UPROPERTIES - - -
	// - - - Variables - - -
	
	// - - - Constructor - - -
	ASimpleGoal();
	
	// - - - Standard Functions - - -
	virtual void Tick(float DeltaTime) override;
	
	
	// - - - UFUNCTIONS - - -
	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// - - - Functions - - -
protected:
	// - - - UPROPERTIES - - -
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	// - - - Variables - - -

	// - - - Standard Functions - - -
	virtual void BeginPlay() override;
	
	// - - - UFUNCTIONS - - -
	// - - - Functions - - -

private:
	// - - - UPROPERTIES - - -
	// - - - Variables - - -
	// - - - Standard Functions - - -
	// - - - UFUNCTIONS - - -
	// - - - Functions - - -
	void SetupCollisions();

};
