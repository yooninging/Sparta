// CXGameStateBase.cpp


#include "ChBGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/ChBPlayerController.h"

void AChBGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			AChBPlayerController* CXPC = Cast<AChBPlayerController>(PC);
			if (IsValid(CXPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				CXPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}
