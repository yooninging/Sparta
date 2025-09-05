// CXGameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChBGameModeBase.generated.h"

class AChBPlayerController;

/**
 * 
 */
UCLASS()
class CHATX_API AChBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void OnPostLogin(AController* NewPlayer) override;

	FString GenerateSecretNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	virtual void BeginPlay() override;
	
	void PrintChatMessageString(AChBPlayerController* InChattingPlayerController, const FString& InChatMessageString);
	
	void IncreaseGuessCount(AChBPlayerController* InChattingPlayerController);

	void ResetGame();

	void JudgeGame(AChBPlayerController* InChattingPlayerController, int InStrikeCount);

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<AChBPlayerController>> AllPlayerControllers;
	
	
};
