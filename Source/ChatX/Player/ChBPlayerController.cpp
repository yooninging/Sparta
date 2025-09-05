// CXPlayerController.cpp


#include "Player/ChBPlayerController.h"
#include "UI/ChBChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ChatX.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ChBGameModeBase.h"
#include "ChBPlayerState.h"
#include "Net/UnrealNetwork.h"

AChBPlayerController::AChBPlayerController()
{
	bReplicates = true;
}

void AChBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}
	
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UChBChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void AChBPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	/*
	ChatMessageString = InChatMessageString;

//	PrintChatMessageString(ChatMessageString);
	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);		
	}
	*/

	ChatMessageString = InChatMessageString;
	
	if (IsLocalController() == true)
	{
		// ServerRPCPrintChatMessageString(InChatMessageString);

		AChBPlayerState* CXPS = GetPlayerState<AChBPlayerState>();
		if (IsValid(CXPS) == true)
		{
		//	FString CombinedMessageString = CXPS->PlayerNameString + TEXT(": ") + InChatMessageString;
			FString CombinedMessageString = CXPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}

void AChBPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
//	UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);
/*
	FString NetModeString = ChatXFunctionLibrary::GetNetModeString(this);
	FString CombinedMessageString = FString::Printf(TEXT("%s: %s"), *NetModeString, *InChatMessageString);
	ChatXFunctionLibrary::MyPrintString(this, CombinedMessageString, 10.f);
*/
	
	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}


void AChBPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AChBPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	/*
	for (TActorIterator<ACXPlayerController> It(GetWorld()); It; ++It)
	{
		ACXPlayerController* CXPlayerController = *It;
		if (IsValid(CXPlayerController) == true)
		{
			CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
		}
	}
	*/

	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		AChBGameModeBase* CXGM = Cast<AChBGameModeBase>(GM);
		if (IsValid(CXGM) == true)
		{
			CXGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

void AChBPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

