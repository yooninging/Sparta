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
	// 메인루트 컴포넌트로 사용되는 Scene컴포넌트를 생성하고(SceneRoot), 이를 staticmeshcomp는 생성하고 붙인다.(루트 컴포넌트의 자손이기 때문에)

	// '/Game/Resources/Props/SM_Chair.SM_Chair' 언리얼에서 원하는 매쉬의 레퍼런스를 복사, 코드에 붙여넣기하면 해당 파일의 위치를 얻을 수 있다.
	// '/Game/Resources/Materials/M_CobbleStone_Smooth.M_CobbleStone_Smooth' 머티리얼도 마찬가지

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	// 경로를 통해 매쉬를 가져온 함수
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_CobbleStone_Smooth.M_CobbleStone_Smooth"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
		// 다만 마테리얼은 매쉬랑 달리 여러가지가 합칠 수 있는 요소. 그래서 위의 매쉬랑 달리 번수가 필요하다. 
	}

	UE_LOG(LogSparta, Warning, TEXT("%s Constructor"), *GetName());


	// 틱 함수를 활성화, 틱 함수에 사용하는 RotationSpeed 초기화.
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
	// Warning 주황색, Display 하얀색
	UE_LOG(LogSparta, Error, TEXT("My LogSparta!"));

	UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());


	// 2강
	SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f)); //짐벌락 문제. FQuat. 쿼터니언이라고 Rotator의 문제인 짐벌락 문제를 해결할 수 있는 수단이 있다. 궁금하면 검색.
	// pitch, yaw, roll  // Y축, X축, Z축
	SetActorScale3D(FVector(2.0f, 1.0f, 1.0f));
	// 	SetActorScale3D(FVector(2.0f)); // 이러면 3개축이 모두 2.0f로 설정된다.

	FVector NewLocation(300.0f, 200.0f, 100.0f);
	FRotator NewRotation(0.0f, 90.0f, 0.0f);
	FVector NewScale(2.0f);

	FTransform NewTransform(NewRotation, NewLocation, NewScale);
	SetActorTransform(NewTransform);  // 트랜스폼을 모두 함께 변경하는 함수. 



}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	AddActorLocalRotation(FRotator(0.0f, RotationSpeed, 0.0f));
	// 근데 이건 문제임. 매 프레임마다 도는 함수임. 그래서 프레임이 120프레임이면 1초에 120번 호출되어 120번 돌아간대. 그래서 DeltaTime을 사용함. DeltaTime = 1초 / 장치 프레임 
	// 즉, 1초에 90도씩 회전할려면 90 / 프레임.
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


// 라이프 사이클 함수?
// 생성자 - 메모리에 생김. 딱 한 번 호출.
// PostInitializeComponents - 컴포넌트가 완성된 직후 호출. 컴포넌트끼리 데이터 주고받기, 상호작용
// BeginPlay() - 배치 (Spawn) 직후 
// Tick(float DeltaTime) - 매 프라임마다 호출됨. (대신 틱마다 호출되기때문에 성능을 크게 저하시킬 수 있음.)
// Destroted() - 삭제되기 직전에  호출됨. 
// EndPlay() - 게임 종료, 파괴 (Destroyed()), 레벨 전환

// Destroy() 와 EndPlay()
// 전자는 명시적인 표현, 후자는 실제 플레이랄까
// D 이후 E가 실행되는 형태래. 작게봐도 D는 객체가 터지는거고 E는 실행 종료니까 후자가 더 큰 개념아닐까



void AItem::ResetActorPosition()
{
	SetActorLocation(FVector(FVector::ZeroVector));
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
	UE_LOG(LogSparta, Warning, TEXT("%s ResetActorPosition"), *GetName());
}

