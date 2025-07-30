#pragma once  

#include "CoreMinimal.h"  
#include "GameFramework/GameState.h"  

// Ensure SPARTALEANING_API is defined properly for export/import macros  
#ifndef SPARTALEANING_API  
#define SPARTALEANING_API  
#endif  

#include "SpartaGameState.generated.h"  

UCLASS()  
class SPARTALEANING_API ASpartaGameState : public AGameState  
{  
	GENERATED_BODY()  

public:  
	ASpartaGameState();  

	virtual void BeginPlay() override;  

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")  
	int32 Score;  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")  
	int32 SpawnedCoinCount;  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")  
	int32 CollectedCoinCount;  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")  
	float LevelDuration;  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")  
	int32 CurrentLevelIndex;  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")  
	int32 MaxLevels;  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")  
	TArray<FName> LevelMapNames;  

	FTimerHandle LevelTimerHandle;  
	FTimerHandle HUDUpdateTimerHandle;  

	UFUNCTION(BlueprintPure, Category = "Score")  
	int32 GetScore() const;  
	UFUNCTION(BlueprintCallable, Category = "Score")  
	void AddScore(int32 Amount);  
	UFUNCTION(BlueprintCallable, Category = "Level")  
	void OnGameOver();  

	void StartLevel();  
	void OnLevelTimeUp();  
	void OnCoinCollected();  
	void EndLevel();  
	void UpdateHUD();  
};