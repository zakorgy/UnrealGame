// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SzakdogaPlayerController.generated.h"

UCLASS()
class ASzakdogaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASzakdogaPlayerController();

protected:
	FVector CurrentVelocity;
	FVector CurrentRotation;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Rotate player to the current mouse cursor location. */
	void RotateToCursor();

	void MoveYAxis(float AxisValue);
	void MoveXAxis(float AxisValue);
};


