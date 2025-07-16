// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

DEFINE_LOG_CATEGORY(LogSparta);

// Sets default values
AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	// ���η�Ʈ ������Ʈ�� ���Ǵ� Scene������Ʈ�� �����ϰ�(SceneRoot), �̸� staticmeshcomp�� �����ϰ� ���δ�.(��Ʈ ������Ʈ�� �ڼ��̱� ������)

	// '/Game/Resources/Props/SM_Chair.SM_Chair' �𸮾󿡼� ���ϴ� �Ž��� ���۷����� ����, �ڵ忡 �ٿ��ֱ��ϸ� �ش� ������ ��ġ�� ���� �� �ִ�.
	// '/Game/Resources/Materials/M_CobbleStone_Smooth.M_CobbleStone_Smooth' ��Ƽ���� ��������

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	// ��θ� ���� �Ž��� ������ �Լ�
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_CobbleStone_Smooth.M_CobbleStone_Smooth"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
		// �ٸ� ���׸����� �Ž��� �޸� ���������� ��ĥ �� �ִ� ���. �׷��� ���� �Ž��� �޸� ������ �ʿ��ϴ�. 
	}

	UE_LOG(LogSparta, Warning, TEXT("%s Constructor"), *GetName());


	// ƽ �Լ��� Ȱ��ȭ, ƽ �Լ��� ����ϴ� RotationSpeed �ʱ�ȭ.
	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.f;
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("My LOG!"));
	// Warning ��Ȳ��, Display �Ͼ��
	UE_LOG(LogSparta, Error, TEXT("My LogSparta!"));

	UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());


	// 2��
	SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f)); //������ ����. FQuat. ���ʹϾ��̶�� Rotator�� ������ ������ ������ �ذ��� �� �ִ� ������ �ִ�. �ñ��ϸ� �˻�.
	// pitch, yaw, roll  // Y��, X��, Z��
	SetActorScale3D(FVector(2.0f, 1.0f, 1.0f));
	// 	SetActorScale3D(FVector(2.0f)); // �̷��� 3������ ��� 2.0f�� �����ȴ�.

	FVector NewLocation(300.0f, 200.0f, 100.0f);
	FRotator NewRotation(0.0f, 90.0f, 0.0f);
	FVector NewScale(2.0f);

	FTransform NewTransform(NewRotation, NewLocation, NewScale);
	SetActorTransform(NewTransform);  // Ʈ�������� ��� �Բ� �����ϴ� �Լ�. 



}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	AddActorLocalRotation(FRotator(0.0f, RotationSpeed, 0.0f));
	// �ٵ� �̰� ������. �� �����Ӹ��� ���� �Լ���. �׷��� �������� 120�������̸� 1�ʿ� 120�� ȣ��Ǿ� 120�� ���ư���. �׷��� DeltaTime�� �����. DeltaTime = 1�� / ��ġ ������ 
	// ��, 1�ʿ� 90���� ȸ���ҷ��� 90 / ������.
	AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));

	if (!FMath::IsNearlyZero(RotationSpeed))
	{

	}

}

void AItem::Destroyed()
{
	UE_LOG(LogSparta, Warning, TEXT("%s Destroyed"), *GetName());

	Super::Destroyed();
}

void AItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogSparta, Warning, TEXT("%s EndPlay"), *GetName());

	Super::EndPlay(EndPlayReason);
}


// ������ ����Ŭ �Լ�?
// ������ - �޸𸮿� ����. �� �� �� ȣ��.
// PostInitializeComponents - ������Ʈ�� �ϼ��� ���� ȣ��. ������Ʈ���� ������ �ְ�ޱ�, ��ȣ�ۿ�
// BeginPlay() - ��ġ (Spawn) ���� 
// Tick(float DeltaTime) - �� �����Ӹ��� ȣ���. (��� ƽ���� ȣ��Ǳ⶧���� ������ ũ�� ���Ͻ�ų �� ����.)
// Destroted() - �����Ǳ� ������  ȣ���. 
// EndPlay() - ���� ����, �ı� (Destroyed()), ���� ��ȯ

// Destroy() �� EndPlay()
// ���ڴ� ������� ǥ��, ���ڴ� ���� �÷��̶���
// D ���� E�� ����Ǵ� ���·�. �۰Ժ��� D�� ��ü�� �����°Ű� E�� ���� ����ϱ� ���ڰ� �� ū ����ƴұ�



void AItem::ResetActorPosition()
{
	SetActorLocation(FVector(FVector::ZeroVector));
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
	UE_LOG(LogSparta, Warning, TEXT("%s ResetActorPosition"), *GetName());
}

