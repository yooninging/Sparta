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
	// ����, ����, ����
	// ����, ���� - ��� �ߵ��� - ������
	// ���� - ���� ���� ������ -  �ߵ��� 5�� �� ���� - ������ - ������
	
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OtherlappedComp, // ��
		AActor* OtherActor, // ��
		UPrimitiveComponent* OtherComp, // ���� ���� �ε�����
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0; // �����۰� �������� ���۵Ǿ��� �� ȣ��Ǵ� �Լ�
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OtherlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0; // ���������

	virtual void DestroyItem() = 0; // �������� �ı��ϴ� �Լ�
	virtual void ActivateItem(AActor* Activator) = 0;
	virtual FName GetItemType() const = 0; // �����Լ��� 0�� ���̸� �ݵ�� �����ؾ��ϴ� ���� ���� �Լ�. �������̽��ϱ� �̷�������
	

};
