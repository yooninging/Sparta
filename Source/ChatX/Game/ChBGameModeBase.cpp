// CXGameModeBase.cpp


#include "Game/ChBGameModeBase.h"
#include "ChBGameStateBase.h"
#include "Player/ChBPlayerController.h"
#include "EngineUtils.h"
#include "Player/ChBPlayerState.h"

void AChBGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	/*
	ACXGameStateBase* CXGameStateBase =  GetGameState<ACXGameStateBase>();
	if (IsValid(CXGameStateBase) == true)
	{
		CXGameStateBase->MulticastRPCBroadcastLoginMessage(TEXT("XXXXXXX"));
	}

	ACXPlayerController* CXPlayerController = Cast<ACXPlayerController>(NewPlayer);
	if (IsValid(CXPlayerController) == true)
	{
		AllPlayerControllers.Add(CXPlayerController);
	}
	*/

	AChBPlayerController* CXPlayerController = Cast<AChBPlayerController>(NewPlayer);
	if (IsValid(CXPlayerController) == true)
	{
		CXPlayerController->NotificationText = FText::FromString(TEXT("Connected to the game server."));
		
		AllPlayerControllers.Add(CXPlayerController);

		AChBPlayerState* CXPS = CXPlayerController->GetPlayerState<AChBPlayerState>();
		if (IsValid(CXPS) == true)
		{
			CXPS->PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
		}

		AChBGameStateBase* CXGameStateBase =  GetGameState<AChBGameStateBase>();
		if (IsValid(CXGameStateBase) == true)
		{
			CXGameStateBase->MulticastRPCBroadcastLoginMessage(CXPS->PlayerNameString);
		}
	}
}

FString AChBGameModeBase::GenerateSecretNumber()
{
	TArray<int32> Numbers;
	for (int32 i = 1; i <= 9; ++i)
	{
		Numbers.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());
	Numbers = Numbers.FilterByPredicate([](int32 Num) { return Num > 0; });
	
	FString Result;
	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}

	return Result;
}

bool AChBGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do {

		if (InNumberString.Len() != 3)
		{
			break;
		}

		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}
			
			UniqueDigits.Add(C);
		}

		if (bIsUnique == false)
		{
			break;
		}

		bCanPlay = true;
		
	} while (false);	

	return bCanPlay;
}

FString AChBGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else 
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;				
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void AChBGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
}

void AChBGameModeBase::PrintChatMessageString(AChBPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	int Index = InChatMessageString.Len() - 3;
	FString GuessNumberString = InChatMessageString.RightChop(Index);
	if (IsGuessNumberString(GuessNumberString) == true)
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);

		IncreaseGuessCount(InChattingPlayerController);
		
		for (TActorIterator<AChBPlayerController> It(GetWorld()); It; ++It)
		{
			AChBPlayerController* CXPlayerController = *It;
			if (IsValid(CXPlayerController) == true)
			{
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				CXPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);

				int32 StrikeCount = FCString::Atoi(*JudgeResultString.Left(1));
				JudgeGame(InChattingPlayerController, StrikeCount);
			}
		}
	}
	else
	{
		for (TActorIterator<AChBPlayerController> It(GetWorld()); It; ++It)
		{
			AChBPlayerController* CXPlayerController = *It;
			if (IsValid(CXPlayerController) == true)
			{
				CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}
}

void AChBGameModeBase::IncreaseGuessCount(AChBPlayerController* InChattingPlayerController)
{
	AChBPlayerState* CXPS = InChattingPlayerController->GetPlayerState<AChBPlayerState>();
	if (IsValid(CXPS) == true)
	{
		CXPS->CurrentGuessCount++;
	}
}

void AChBGameModeBase::ResetGame()
{
	SecretNumberString = GenerateSecretNumber();

	for (const auto& CXPlayerController : AllPlayerControllers)
	{
		AChBPlayerState* CXPS = CXPlayerController->GetPlayerState<AChBPlayerState>();
		if (IsValid(CXPS) == true)
		{
			CXPS->CurrentGuessCount = 0;
		}
	}
}

void AChBGameModeBase::JudgeGame(AChBPlayerController* InChattingPlayerController, int InStrikeCount)
{
	if (3 == InStrikeCount)
	{
		AChBPlayerState* CXPS = InChattingPlayerController->GetPlayerState<AChBPlayerState>();
		for (const auto& CXPlayerController : AllPlayerControllers)
		{
			if (IsValid(CXPS) == true)
			{
				FString CombinedMessageString = CXPS->PlayerNameString + TEXT(" has won the game.");
				CXPlayerController->NotificationText = FText::FromString(CombinedMessageString);

				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& CXPlayerController : AllPlayerControllers)
		{
			AChBPlayerState* CXPS = CXPlayerController->GetPlayerState<AChBPlayerState>();
			if (IsValid(CXPS) == true)
			{
				if (CXPS->CurrentGuessCount < CXPS->MaxGuessCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}

		if (true == bIsDraw)
		{
			for (const auto& CXPlayerController : AllPlayerControllers)
			{
				CXPlayerController->NotificationText = FText::FromString(TEXT("Draw..."));

				ResetGame();
			}
		}
	}
}

