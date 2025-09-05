// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChBPawn.generated.h"

UCLASS()
class CHATX_API AChBPawn : public APawn
{
	GENERATED_BODY()

public:
//	ACXPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
};
