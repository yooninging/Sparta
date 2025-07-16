// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSparta, Warning, All);
// 워닝로그를 직접 만들기. (기본 Warning이지만 모든 로그를 할 순 있다.

UCLASS()
class SPARTAUNREALCPP_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Categoty="Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintrereadWrite, Category="Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BLueprintReadOnly, Categoty="Item|Properties")
	float RotationSpeed;

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BluepriontCallable, Category="Item|Actions")
	void ResetActorPosition();
	// 블루프린트에서 콜할 수 있다

	UFUNCTION(BlueprintPure, Category = "Item|Actions")
	float GetPotationSpeed() const;
	// 블루프린트에서 값만 받는다

	UFUNCTION(BlueprirntImplementableEvent, Category="Item|Event")
	void OnItemPickUP();
	// 블루프린트에서 구현했는데 반대로 C++에서 볼 수 있다.
};
