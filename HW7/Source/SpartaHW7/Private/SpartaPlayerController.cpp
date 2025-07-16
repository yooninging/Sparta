// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "SpartaPawn.h"

ASpartaPlayerController::ASpartaPlayerController()
    : InputMappingContext(nullptr),
    MoveAction(nullptr),
    LookAction(nullptr)
{
}

void ASpartaPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
				Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }
}

