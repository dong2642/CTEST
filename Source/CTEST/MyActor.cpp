// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "MyPawn.h"
#include "TimerTest.h"
#include "Components/SphereComponent.h"

#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


DEFINE_LOG_CATEGORY(LogMyActor);

// Sets default values
AMyActor::AMyActor()
{	
	// 가장 기본적으로 생성되는 생성자입니다. 여기서 클래스 디폴트 오브젝트 프로퍼티를 초기화합니다.
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		m_cone(TEXT("StaticMesh'/Game/P38/Meshes/SM_Rocket.SM_Rocket'"));

	static ConstructorHelpers::FObjectFinder<UMaterial>
		m_mat(TEXT("MaterialInstanceConstant'/Game/P38/Materials/MI_Rocket.MI_Rocket'"));

	UStaticMeshComponent* mMesh = CreateDefaultSubobject
		<UStaticMeshComponent>(TEXT("RootMeshComponent"));

	
	mMesh->SetStaticMesh(m_cone.Object);
	mMesh->SetMaterial(0, m_mat.Object);

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	// 키, 시간(초), 컬러, 메세지
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("MyAcotr Beginplay"));	

	GetWorldTimerManager().SetTimer(TimerTestHandle, this, &AMyActor::TimerTest, 3.0f, true);
	
}

void AMyActor::TimerTest()
{

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("1"));

	//UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));


	//// 유형으로 액터 찾기 (UWrold 오브젝트 필요)
	//for (TActorIterator<AMyActor> actor(GetWorld()); actor; ++actor)
	//{
	//	UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor->GetActorTransform());
	//	actor->Destroy();
	//}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(0, 0, 1));
	
	if (bIsSmaller)
	{
		SetActorScale3D(GetActorScale3D() * 0.95f);
	}

	// UE_LOG(카테고리, 상세도, 메세지);
	//UE_LOG(LogMyActor, Error, TEXT("MyActor Tick"));
	

	/*로그 상세 수준
	 로그 상세 수준의 종류는 다음과 같다.
	 Fatal 수준 로그는 항상 콘솔 및 로그 파일에 출력되며 로그가 비활성화된 경우에도 작동이 중단된다.
	 Error 수준 로그는 콘솔 및  로그 파일에 출력되며, 이 로그는 기본적으로 빨간색으로 표시된다.
	 Warning 수준 로그는 콘솔 및 로그 파일에 출력되며, 이 로그는 기본적으로 노란색으로 표시된다.
	 Display 수준 로그는 콘솔 및 로그 파일에 출력된다.
	 Log 수준 로그는 로그 파일에는 출력되지만, 게임 내의 콘솔에서는 출력되지 않지만, 에디터의 출력 로그 탭을 통해서는 계속 출력된다.
	 Verbose 수준의 로그는 로그 파일에는 출력되자먼, 게임 내의 콘솔에는 출력되지 않는다. 일반적으로 자세한 로깅 및 디버깅에 사용된다.
	 VeryVerbose 수준의 로그는 로그 파일에는 출력되지만, 게임 내의 콘솔에는 출력되지 않는다.
	 이수준의 로그는 일반적으로 대량의 로그를 출력하는 상세한 로깅에 사용된다.
	*/
}





	