// Fill out your copyright notice in the Description page of Project Settings.


#include "Balls/SimpleBall.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Paddles/AIPaddle.h"
#include "Paddles/PlayerPaddle.h"
#include "PongleGameStateBase.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PUBLIC LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Constructor
ASimpleBall::ASimpleBall()
{
	PrimaryActorTick.bCanEverTick = true;

	SetupCollisions();
	SetupMovementComponent();
}

// Standard Functions
void ASimpleBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (GEngine) GEngine->AddOnScreenDebugMessage(5, 10, FColor::Magenta, FString::Printf(TEXT("Ball Velocity: %s"), *MovementComponent->Velocity.ToString()));
}

// UFUNCTIONS
void ASimpleBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr))
	{
		return;
	}

	FVector HitVelocity = MovementComponent->Velocity;
	StopMovement();
	FVector ReflectedVelocity;
	
	// Hit Player Paddle
	if (APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(OtherActor))
	{	
		float YVelocity = HitVelocity.Y;

		if (PlayerPaddle->GetVelocity().Y != 0)
		{
			YVelocity += PlayerPaddle->GetVelocity().Y;
		}

		if (YVelocity > MovementComponent->MaxSpeed)
		{
			YVelocity = MovementComponent->MaxSpeed;
		}
		else if (YVelocity < -MovementComponent->MaxSpeed)
		{
			YVelocity = -MovementComponent->MaxSpeed;
		}
		
		if (GetActorLocation().X < PlayerPaddle->GetActorLocation().X)
		{
			ReflectedVelocity = FVector(HitVelocity.X, YVelocity, 0);
		}
		else
		{
			float XVelocityMagnitude = FMath::Abs<float>(HitVelocity.X);
			ReflectedVelocity = FVector(XVelocityMagnitude, YVelocity, 0);
		}
	}
	// Hit AI Paddle
	// TODO: Specify this as Opposite AI Paddle, or Player 2
	else if (AAIPaddle* AIPaddle = Cast<AAIPaddle>(OtherActor))
	{
		float YVelocity = HitVelocity.Y;

		if (AIPaddle->GetVelocity().Y != 0)
		{
			YVelocity += AIPaddle->GetVelocity().Y;
		}

		if (YVelocity > MovementComponent->MaxSpeed)
		{
			YVelocity = MovementComponent->MaxSpeed;
		}
		else if (YVelocity < -MovementComponent->MaxSpeed)
		{
			YVelocity = -MovementComponent->MaxSpeed;
		}

		if (GetActorLocation().X > AIPaddle->GetActorLocation().X)
		{
			ReflectedVelocity = FVector(HitVelocity.X, YVelocity, 0);
		}
		else
		{
			float XVelocityMagnitude = FMath::Abs<float>(HitVelocity.X);
			ReflectedVelocity = FVector(-XVelocityMagnitude, YVelocity, 0);
		}
	}
	// Hit Wall
	// TODO: Change this for Player's 3 and 4
	else
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(4, 5, FColor::Red, "Inside Wall Logic");

		ReflectedVelocity = FVector(HitVelocity.X, -HitVelocity.Y, 0);
	}

	// If Ball won't move up or down
	if (ReflectedVelocity.X == 0)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(5, 5, FColor::Red, "Needs to Move Up or Down");
		float Random = FMath::RandRange(-1, 1);

		ReflectedVelocity.X = MovementComponent->MaxSpeed;
		if (Random < 0)
		{
			ReflectedVelocity.X *= -1;
		}
	}

	//if (GEngine) GEngine->AddOnScreenDebugMessage(3, 10, FColor::Cyan, FString::Printf(TEXT("Velocity Before: %s"), *MovementComponent->Velocity.ToString()));
	MovementComponent->Velocity = ReflectedVelocity;
	//if (GEngine) GEngine->AddOnScreenDebugMessage(4, 10, FColor::Cyan, FString::Printf(TEXT("Velocity After: %s"), *MovementComponent->Velocity.ToString()));
}

void ASimpleBall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// This is for scorekeeping
	Super::NotifyActorBeginOverlap(OtherActor);

	//if (GEngine) GEngine->AddOnScreenDebugMessage(9, 10, FColor::Red, "Entered Any Goal");

	if (OtherActor->Tags.Contains(FName("Goal_Player")))
	{
		/*if (GEngine) GEngine->AddOnScreenDebugMessage(10, 10, FColor::Red, "Entered Player Goal");*/

		UWorld* const World = GetWorld();
		if (World)
		{
			APongleGameStateBase* GameState = Cast<APongleGameStateBase>(World->GetGameState());

			GameState->AddAIPoint();
		}
	}

	if (OtherActor->Tags.Contains(FName("Goal_AI1")))
	{
		/*if (GEngine) GEngine->AddOnScreenDebugMessage(10, 10, FColor::Red, "Entered AI Goal");*/
		UWorld* const World = GetWorld();
		if (World)
		{
			APongleGameStateBase* GameState = Cast<APongleGameStateBase>(World->GetGameState());

			GameState->AddPlayerPoint();
		}
	}

}

// Functions
FVector ASimpleBall::GetVelocity() const
{
	return MovementComponent->Velocity;
}

void ASimpleBall::FireInDirection(const FVector& Direction)
{
	MovementComponent->Velocity = Direction * MovementComponent->MaxSpeed/4;
}

void ASimpleBall::StopMovement()
{
	MovementComponent->Velocity = FVector::ZeroVector;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PROTECTED LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Standard Functions
void ASimpleBall::BeginPlay()
{
	Super::BeginPlay();

	FireInDirection(FVector::BackwardVector);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PRIVATE LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Functions
void ASimpleBall::SetupCollisions()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");

	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASimpleBall::OnHit);
	
	SetRootComponent(CollisionComponent);

	VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Component"));
	VisualComponent->BodyInstance.SetCollisionProfileName("NoCollision");
	VisualComponent->SetupAttachment(GetRootComponent());
}

void ASimpleBall::SetupMovementComponent()
{
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->SetUpdatedComponent(CollisionComponent);
	MovementComponent->InitialSpeed = 0;
	MovementComponent->MaxSpeed = MaxSpeed;
	MovementComponent->bRotationFollowsVelocity = false;
	MovementComponent->bShouldBounce = true;
	MovementComponent->Bounciness = .3;
	MovementComponent->ProjectileGravityScale = 0;
}