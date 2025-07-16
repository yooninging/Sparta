// Fill out your copyright notice in the Description page of Project Settings.

#include "SpartaPawn.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"



// Sets default values
ASpartaPawn::ASpartaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;
	CapsuleComp->InitCapsuleSize(42.0f, 96.0f);
	CapsuleComp->SetCollisionProfileName(TEXT("Pawn"));

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	SkeletalMeshComp->SetupAttachment(RootComponent);
	SkeletalMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	if (MeshAsset.Succeeded())
			{
		SkeletalMeshComp->SetSkeletalMesh(MeshAsset.Object);
	}

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
	

}

// Called when the game starts or when spawned
void ASpartaPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpartaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}






// Called to bind functionality to input
void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController && PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Move
				);
			}
			if (PlayerController && PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Look
				);
			}
		}
	}
}


void ASpartaPawn::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveValue.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveValue.X);
	}

	if (!FMath::IsNearlyZero(MoveValue.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveValue.Y);
	}
}

void ASpartaPawn::Look(const FInputActionValue& Value)
{
    FVector2D LookValue = Value.Get<FVector2D>();

    AddControllerYawInput(LookValue.X);
    AddControllerPitchInput(LookValue.Y);
}
