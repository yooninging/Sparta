// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpartaHW7GameMode.h"
#include "SpartaHW7Character.h"
#include "UObject/ConstructorHelpers.h"

ASpartaHW7GameMode::ASpartaHW7GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
