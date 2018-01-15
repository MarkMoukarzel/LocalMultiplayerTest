// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LocalMultiplayerTestGameMode.h"
#include "LocalMultiplayerTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALocalMultiplayerTestGameMode::ALocalMultiplayerTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
