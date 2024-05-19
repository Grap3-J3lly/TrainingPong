// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddles/Paddle.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PUBLIC LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Constructor
APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	SetRootComponent(CollisionComponent);

	VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Component"));
	VisualComponent->SetupAttachment(GetRootComponent());

	SetupCollision();

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
}

// Standard Functions
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = FVector(PaddleXValue, GetActorLocation().Y, 130);
	SetActorLocation(Location);
}

void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector APaddle::GetVelocity() const
{
	return MovementComponent->Velocity;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PROTECTED LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Standard Functions
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
	PaddleXValue = GetActorLocation().X;
}

// UFUNCTIONS
void APaddle::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Paddle Hit");
	}*/
}

// Functions
void APaddle::Move(float AxisValue)
{

}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PRIVATE LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Functions
void APaddle::SetupCollision()
{
	VisualComponent->BodyInstance.SetCollisionProfileName("NoCollision");
	CollisionComponent->BodyInstance.SetCollisionProfileName("Pawn");

	CollisionComponent->OnComponentHit.AddDynamic(this, &APaddle::OnHit);
}