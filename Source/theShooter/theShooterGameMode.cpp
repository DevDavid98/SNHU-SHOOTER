// Copyright Epic Games, Inc. All Rights Reserved.

#include "theShooterGameMode.h"
#include "theShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AtheShooterGameMode::AtheShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
