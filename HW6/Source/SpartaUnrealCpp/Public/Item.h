// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSparta, Warning, All);
// ���׷α׸� ���� �����. (�⺻ Warning������ ��� �α׸� �� �� �ִ�.

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
	// �������Ʈ���� ���� �� �ִ�

	UFUNCTION(BlueprintPure, Category = "Item|Actions")
	float GetPotationSpeed() const;
	// �������Ʈ���� ���� �޴´�

	UFUNCTION(BlueprirntImplementableEvent, Category="Item|Event")
	void OnItemPickUP();
	// �������Ʈ���� �����ߴµ� �ݴ�� C++���� �� �� �ִ�.
};
