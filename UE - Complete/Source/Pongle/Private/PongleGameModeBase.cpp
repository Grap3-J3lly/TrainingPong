// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongleGameModeBase.h"

#include "Paddles/PlayerPaddle.h"
#include "PongleGameStateBase.h"

// Constructor
APongleGameModeBase::APongleGameModeBase()
{
	DefaultPawnClass = APlayerPaddle::StaticClass();
	GameStateClass = APongleGameStateBase::StaticClass();
}

// Functions
void APongleGameModeBase::StartPlay()
{
	Super::StartPlay();

	UWorld* const World = GetWorld();

	if (World)
	{
		APongleGameStateBase* PongleGameState = World->GetGameState<APongleGameStateBase>();
		PongleGameState->StartGame();
	}
}