// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentX = 0;
	CurrentY = 0;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	Move();
}

int32 AMyActor::Step()
{
	return FMath::RandRange(0, 1);
}

void AMyActor::Move()
{
	UE_LOG(LogTemp, Warning, TEXT("시작 위치 : (X = %d, Y = %d)"), CurrentX, CurrentY);
	
	for (int32 i = 0; i < 10; ++i)
	{
		int32 DeltaX = Step();
		int32 DeltaY = Step();

		CurrentX += DeltaX;
		CurrentY += DeltaY;

	}


// Log the current position
	UE_LOG(LogTemp, Warning, TEXT("이동 후 위치 : X = %d, Y = %d"), CurrentX, CurrentY);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

