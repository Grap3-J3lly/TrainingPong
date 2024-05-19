// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleWall.generated.h"

// Forward Declarations
class UBoxComponent;

UCLASS()
class PONGLE_API ASimpleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	ASimpleWall();
	
	// Standard Functions
	virtual void Tick(float DeltaTime) override;

protected:
	// Standard Functions
	virtual void BeginPlay() override;
	
	// UFUNCTIONS
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	// UPROPERTIES
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualComponent;

	// Functions
	void SetupCollision();
};
