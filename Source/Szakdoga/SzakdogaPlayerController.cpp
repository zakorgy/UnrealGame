// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SzakdogaPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "SzakdogaCharacter.h"

UPROPERTY(EditAnywhere, BlueprintReadWrite)
const float ROTATION_TERSHOLD = 0.1f;

ASzakdogaPlayerController::ASzakdogaPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	if (APawn* MyPawn = GetPawn()) {
		CurrentRotation = MyPawn->GetActorRotation().Euler();
	}
	else {
		CurrentRotation = FVector(0.0);
	}
}

void ASzakdogaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (!CurrentVelocity.IsZero())
	{
		if (ASzakdogaCharacter* MyPawn = Cast<ASzakdogaCharacter>(GetPawn()))
		{
			FVector ActorLocation = MyPawn->GetActorLocation();
			MyPawn->SetActorLocation(ActorLocation + CurrentVelocity * MyPawn->GetMovementSpeed(), true);
		}
	}
	RotateToCursor();
}

void ASzakdogaPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveRight", this, &ASzakdogaPlayerController::MoveYAxis);
	InputComponent->BindAxis("MoveForward", this, &ASzakdogaPlayerController::MoveXAxis);
}

void ASzakdogaPlayerController::RotateToCursor()
{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (APawn* MyPawn = GetPawn()) {
			FRotator Rotation = (Hit.Location - MyPawn->GetActorLocation()).Rotation();
			FVector EulerRotation = Rotation.Euler();
			if (FMath::Abs(EulerRotation.Y - CurrentRotation.Y) > ROTATION_TERSHOLD) {
				// NOTE: Current rotation shule be just a float
				CurrentRotation = EulerRotation;
				MyPawn->SetActorRotation(FRotator(0.0f, Rotation.Yaw, 0.0f));
			}
		}
}

void ASzakdogaPlayerController::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

void ASzakdogaPlayerController::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}
