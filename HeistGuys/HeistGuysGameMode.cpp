// Copyright Epic Games, Inc. All Rights Reserved.

#include "HeistGuysGameMode.h"
#include "HeistGuysCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHeistGuysGameMode::AHeistGuysGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
