// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SzakdogaGameMode.h"
#include "SzakdogaPlayerController.h"
#include "SzakdogaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASzakdogaGameMode::ASzakdogaGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASzakdogaPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}