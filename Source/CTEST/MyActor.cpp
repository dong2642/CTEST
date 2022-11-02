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
	// ���� �⺻������ �����Ǵ� �������Դϴ�. ���⼭ Ŭ���� ����Ʈ ������Ʈ ������Ƽ�� �ʱ�ȭ�մϴ�.
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
	// Ű, �ð�(��), �÷�, �޼���
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("MyAcotr Beginplay"));	

	GetWorldTimerManager().SetTimer(TimerTestHandle, this, &AMyActor::TimerTest, 3.0f, true);
	
}

void AMyActor::TimerTest()
{

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("1"));

	//UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));


	//// �������� ���� ã�� (UWrold ������Ʈ �ʿ�)
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

	// UE_LOG(ī�װ�, �󼼵�, �޼���);
	//UE_LOG(LogMyActor, Error, TEXT("MyActor Tick"));
	

	/*�α� �� ����
	 �α� �� ������ ������ ������ ����.
	 Fatal ���� �α״� �׻� �ܼ� �� �α� ���Ͽ� ��µǸ� �αװ� ��Ȱ��ȭ�� ��쿡�� �۵��� �ߴܵȴ�.
	 Error ���� �α״� �ܼ� ��  �α� ���Ͽ� ��µǸ�, �� �α״� �⺻������ ���������� ǥ�õȴ�.
	 Warning ���� �α״� �ܼ� �� �α� ���Ͽ� ��µǸ�, �� �α״� �⺻������ ��������� ǥ�õȴ�.
	 Display ���� �α״� �ܼ� �� �α� ���Ͽ� ��µȴ�.
	 Log ���� �α״� �α� ���Ͽ��� ��µ�����, ���� ���� �ֿܼ����� ��µ��� ������, �������� ��� �α� ���� ���ؼ��� ��� ��µȴ�.
	 Verbose ������ �α״� �α� ���Ͽ��� ��µ��ڸ�, ���� ���� �ֿܼ��� ��µ��� �ʴ´�. �Ϲ������� �ڼ��� �α� �� ����뿡 ���ȴ�.
	 VeryVerbose ������ �α״� �α� ���Ͽ��� ��µ�����, ���� ���� �ֿܼ��� ��µ��� �ʴ´�.
	 �̼����� �α״� �Ϲ������� �뷮�� �α׸� ����ϴ� ���� �α뿡 ���ȴ�.
	*/
}





	