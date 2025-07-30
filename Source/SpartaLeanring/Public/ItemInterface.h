// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPARTALEANRING_API IItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 지뢰, 힐링, 코인
	// 히링, 코인 - 즉시 발동형 - 오러랩
	// 지뢰 - 범위 내에 오버랩 -  발동이 5초 뒤 폭팔 - 오버랩 - 데미지
	
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OtherlappedComp, // 나
		AActor* OtherActor, // 너
		UPrimitiveComponent* OtherComp, // 너의 뭐가 부딪혔음
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0; // 아이템과 오버랩이 시작되었을 때 호출되는 함수
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OtherlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0; // 엔드오버랩

	virtual void DestroyItem() = 0; // 아이템을 파괴하는 함수
	virtual void ActivateItem(AActor* Activator) = 0;
	virtual FName GetItemType() const = 0; // 가상함수에 0을 붙이면 반드시 구현해야하는 순수 가상 함수. 인터페이스니까 이런식으로
	

};
