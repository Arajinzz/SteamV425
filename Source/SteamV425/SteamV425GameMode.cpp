// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamV425GameMode.h"
#include "SteamV425Character.h"
#include "UObject/ConstructorHelpers.h"

ASteamV425GameMode::ASteamV425GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
