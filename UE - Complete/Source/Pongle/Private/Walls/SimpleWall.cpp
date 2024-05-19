// Fill out your copyright notice in the Description page of Project Settings.


#include "Walls/SimpleWall.h"

#include "Components/BoxComponent.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PUBLIC LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Constructor
ASimpleWall::ASimpleWall()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	SetRootComponent(CollisionComponent);

	VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Component"));
	VisualComponent->SetupAttachment(GetRootComponent());

	SetupCollision();
}

// Standard Functions
void ASimpleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PROTECTED LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Standard Functions
void ASimpleWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Functions
void ASimpleWall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Cyan, "Wall Hit");
	}*/
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PRIVATE LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Functions
void ASimpleWall::SetupCollision()
{
	VisualComponent->BodyInstance.SetCollisionProfileName("NoCollision");
	CollisionComponent->BodyInstance.SetCollisionProfileName("Wall");

	CollisionComponent->OnComponentHit.AddDynamic(this, &ASimpleWall::OnHit);
}