// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PONGLE_API APongleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Constructor
	APongleGameModeBase();

	// Functions
	virtual void StartPlay() override;
};
