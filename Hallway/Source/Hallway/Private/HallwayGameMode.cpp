// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Hallway.h"
#include "HallwayGameMode.h"
#include "HallwayHUD.h"
#include "HallwayCharacter.h"
#include "HorrorGameState.h"

AHallwayGameMode::AHallwayGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	GameStateClass = AHorrorGameState::StaticClass();
	
	// use our custom HUD class
	HUDClass = AHallwayHUD::StaticClass();
}
