// Fill out your copyright notice in the Description page of Project Settings.


#include "PongleGameStateBase.h"
#include "Balls/SimpleBall.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Paddles/AIPaddle.h"
#include "Paddles/PlayerPaddle.h"
#include "PongleGameModeBase.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PUBLIC LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

// Constructor
APongleGameStateBase::APongleGameStateBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Ball = nullptr;
	BallStartLocation = FVector(0, 0, 130);

	PlayerLocation = FVector(-3940, 0, 130);
	AILocation = FVector(3940, 0, 130);

	IsFirstStart = true;

	CurrentState = EPongleStates::EWaitingToStart;

	AIScore = 0;
	PlayerScore = 0;

	MaxScore = 5;

	LastScore = ELastScored::ENone;
	
}

// UFUNCTIONS
int APongleGameStateBase::GetPlayerScore() const
{
	return PlayerScore;
}

int APongleGameStateBase::GetAIScore() const
{
	return AIScore;
}


// Functions
void APongleGameStateBase::StartGame()
{
	if (IsFirstStart)
	{
		InitLevelActors();
		IsFirstStart = false;
	}
	else
	{
		PlayerScore = 0;
		AIScore = 0;

		CurrentState = EPongleStates::EWaitingToStart;

		if (AIPaddle)
		{
			AIPaddle->SetActorLocation(AILocation);
		}
		if (PlayerPaddle)
		{
			PlayerPaddle->SetActorLocation(PlayerLocation);
		}

		// Enable the keyboard to let the Player Play
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		// Disable Mouse Cursor
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

		// Unset the game to pause.
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(false);
	}
	StartPlaying();
}

void APongleGameStateBase::AddAIPoint()
{
	AIScore++;

	LastScore = ELastScored::EAI;

	ResetTheBall();

	if (IsGameEnded())
	{
		GameEnded();
	}
	else
	{
		LaunchTheBallToAI();
	}
}

void APongleGameStateBase::AddPlayerPoint()
{
	PlayerScore++;

	LastScore = ELastScored::EPlayer;
	ResetTheBall();

	if (IsGameEnded())
	{
		GameEnded();
	}
	else
	{
		LaunchTheBallToPlayer();
	}
}

void APongleGameStateBase::LaunchTheBallToPlayer()
{
	LaunchTheBall(-1);
}

void APongleGameStateBase::LaunchTheBallToAI()
{
	LaunchTheBall(1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -	//
//					PRIVATE LOGIC						//
// - - - - - - - - - - - - - - - - - - - - - - - - - -	//

void APongleGameStateBase::InitLevelActors()
{
	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	Ball = World->SpawnActor<ASimpleBall>(BallClass, BallStartLocation, FRotator::ZeroRotator);
	
	AIPaddle = World->SpawnActor<AAIPaddle>(AIPaddleClass, AILocation, FRotator(0, 180, 0));
	AIPaddle->SetGameBallReference(Ball);
	
	PlayerPaddle = World->SpawnActor<APlayerPaddle>(PlayerPaddleClass, PlayerLocation, FRotator::ZeroRotator);
}

bool APongleGameStateBase::IsGameEnded()
{
	return (PlayerScore >= MaxScore) || (AIScore >= MaxScore);
}

void APongleGameStateBase::GameEnded()
{
	PlayerPaddle->GetHUD()->RemoveFromViewport();
	
	EndScreen = CreateWidget(GetWorld(), EndScreenClass);
	if (EndScreen != nullptr)
	{
		EndScreen->AddToViewport();
	}
}

void APongleGameStateBase::StartPlaying()
{
	CurrentState = EPongleStates::EPlaying;

	UWorld* const world = GetWorld();
	if (world)
	{
		if (LastScore == ELastScored::EAI)
		{
			LaunchTheBallToAI();
		}
		else
		{
			LaunchTheBallToPlayer();
		}
	}
}

void APongleGameStateBase::LaunchTheBall(float XDirection)
{
	if (Ball != nullptr)
	{
		FVector Direction(XDirection, 0, 0);
		Ball->FireInDirection(Direction);
	}
}

void APongleGameStateBase::ResetTheBall()
{
	Ball->StopMovement();
	Ball->SetActorLocation(BallStartLocation);
}