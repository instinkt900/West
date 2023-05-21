// Copyright Epic Games, Inc. All Rights Reserved.

#include "WestGameMode.h"
#include "WestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWestGameMode::AWestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
