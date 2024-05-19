// Fill out your copyright notice in the Description page of Project Settings.


#include "Walls/SimpleGoal.h"

#include "Components/BoxComponent.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PUBLIC LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// - - - Constructor - - -
ASimpleGoal::ASimpleGoal()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	SetRootComponent(CollisionComponent);
}

// - - - Standard Functions - - -
void ASimpleGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// - - - UFUNCTIONS - - -
void ASimpleGoal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PROTECTED LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// - - - Standard Functions - - -
void ASimpleGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PRIVATE LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// - - - Functions - - -
void ASimpleGoal::SetupCollisions()
{
	CollisionComponent->BodyInstance.SetCollisionProfileName("Goal");
	CollisionComponent->SetGenerateOverlapEvents(true);
}