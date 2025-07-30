// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpartaLeanringGameMode.h"
#include "SpartaLeanringCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpartaLeanringGameMode::ASpartaLeanringGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
