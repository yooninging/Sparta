// CXPawn.cpp


#include "ChBPawn.h"
#include "ChatX.h"


void AChBPawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetRoleString = ChatXFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::BeginPlay() %s [%s]"), *ChatXFunctionLibrary::GetNetModeString(this), *NetRoleString);
	ChatXFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void AChBPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = ChatXFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *ChatXFunctionLibrary::GetNetModeString(this), *NetRoleString);
	ChatXFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}
