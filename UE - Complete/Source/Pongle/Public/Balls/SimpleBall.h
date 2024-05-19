// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleBall.generated.h"

// Forward Declarations
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class PONGLE_API ASimpleBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// UPROPERTIES
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 200;

	// Variables
	
	// Constructor
	ASimpleBall();
	
	// Standard Functions
	virtual void Tick(float DeltaTime) override;
	
	// UFUNCTIONS
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Functions
	FVector GetVelocity() const;

	void FireInDirection(const FVector& ShootDirection);
	void StopMovement();

protected:
	// Standard Functions
	virtual void BeginPlay() override;

private:
	// UPROPERTIES
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualComponent;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComponent;

	// Functions
	void SetupCollisions();
	void SetupMovementComponent();
};
