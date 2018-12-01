// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CppFirstPersonFpsGameMode.h"
#include "CppFirstPersonFpsHUD.h"
#include "CppFirstPersonFpsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACppFirstPersonFpsGameMode::ACppFirstPersonFpsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACppFirstPersonFpsHUD::StaticClass();
}
