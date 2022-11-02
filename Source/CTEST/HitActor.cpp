// Fill out your copyright notice in the Description page of Project Settings.


#include "HitActor.h"
#include "MyPawn.h"
#include "MyActor.h"
#include "MyActorComponent.h"
#include "MyDefaultPawn.h"

#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


// Sets default values
AHitActor::AHitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		m_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	
	UStaticMeshComponent* mMesh = CreateDefaultSubobject
		<UStaticMeshComponent>(TEXT("RootMeshComponent"));


	mMesh->SetStaticMesh(m_Sphere.Object);
	RootComponent = mMesh;


	// ���� ����
	mMesh->SetSimulatePhysics(false);

	// �ùķ��̼� �� Hit event�� �����ϵ��� ����
	mMesh->SetNotifyRigidBodyCollision(true);

	// �Լ� ���ε�
	//this->OnActorHit.AddDynamic(this, &AHitActor::OnHit);

	//mMesh->OnComponentHit.AddDynamic(this, &AHitActor::OnComponentHit);
	

	// ������ �̺�Ʈ ���
	mMesh->OnComponentBeginOverlap.AddDynamic(this, &AHitActor::OnOverlapBegin);
	mMesh->SetGenerateOverlapEvents(true);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// MyActorComponent.h �߰�
	// Ŀ���� ������Ʈ�� �����.
	UMyActorComponent* c_component = CreateDefaultSubobject<UMyActorComponent>(TEXT("CustomComponent"));


	// ������Ʈ �±׸� �߰��Ѵ�
	c_component->ComponentTags.Add(FName(TEXT("move")));

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// �浹 ó��

	// �ݸ��� Ÿ�� ����
	mMesh->SetCollisionObjectType(ECC_WorldDynamic);

	// �ڽŰ��� �浹 ����
	mMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	mMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


}

	
	




void AHitActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hit"));

	
}

void AHitActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{/*
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hit"));*/
	
	OtherActor -> TakeDamage(10, FDamageEvent(), NULL, this);

	// ����ȯ ����� ��, ������ ���� ����ȯ�� �Ϸ��� ������Ʈ�� ����ȯ ��� ������Ʈ�� ������ �˻� �õ��ϴ� ���̴�.
	/// Cast<�����ϰ��� �ϴ� ����>(�����ϰ��� �ϴ� ���); 

	// AMyPawn* test
	// if(test) Cast Success / Cast Fail

	// IsValid(Object) true / false

	AMyPawn* Me = Cast<AMyPawn>(OtherActor);
	if (Me)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Cast Success"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Cast Fail"));
	}

	
	
}


// "Overlap Begin: �޼����� ������ �غ��ÿ�.
void AHitActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
}



// Called when the game starts or when spawned
void AHitActor::BeginPlay()
{
	Super::BeginPlay();
	
	// GetComponents() ��� ������Ʈ ��������

	for (UActorComponent* actComp : GetComponents())
	{
		if(actComp->ComponentHasTag(FName(TEXT("move"))))
		{
			UMyActorComponent* myactComp = Cast<UMyActorComponent>(actComp);
			AActor* target = GWorld->GetFirstPlayerController()->GetPawn();
			myactComp->SetFollowTarget(target, 0.5f);
		}
	}
}

// Called every frame
void AHitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}



float AHitActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));


	UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, GetActorTransform());

	


	return 0.0f;
}
