// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongleGameStateBase.generated.h"

class ASimpleBall;
class AAIPaddle;
class APlayerPaddle;

enum class EPongleStates
{
	EWaitingToStart,
	EPlaying,
	EEnded
};

enum class ELastScored
{
	EPlayer,
	EAI,
	ENone
};

UCLASS()
class PONGLE_API APongleGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	// Constructor
	APongleGameStateBase();

	// UFUNCTIONS
	UFUNCTION(BlueprintCallable)
	int GetPlayerScore() const;
	UFUNCTION(BlueprintCallable)
	int GetAIScore() const;
	
	// Functions
	void StartGame();
	void AddAIPoint();
	void AddPlayerPoint();
	void LaunchTheBallToPlayer();
	void LaunchTheBallToAI();

private:
	// UPROPERTIES
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASimpleBall> BallClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APlayerPaddle> PlayerPaddleClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAIPaddle> AIPaddleClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> EndScreenClass;
	UPROPERTY()
	UUserWidget* EndScreen;

	// Variables
	EPongleStates CurrentState;
	bool IsFirstStart;

	ASimpleBall* Ball;
	APlayerPaddle* PlayerPaddle;
	AAIPaddle* AIPaddle;

	FVector BallStartLocation;
	FVector PlayerLocation;
	FVector AILocation;

	// TSubclassOf<UUserWidget> EndMenuClass;
	ELastScored LastScore;
	int AIScore;
	int PlayerScore;
	int MaxScore;

	// Functions
	void InitLevelActors();
	bool IsGameEnded();
	void GameEnded();
	void StartPlaying();
	void LaunchTheBall(float XDirection);
	void ResetTheBall();

};
