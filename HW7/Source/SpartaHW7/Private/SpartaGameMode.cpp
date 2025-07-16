// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameMode.h"
#include "SpartaCharacter.h"

ASpartaGameMode::ASpartaGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ASpartaCharacter::StaticClass();
}

