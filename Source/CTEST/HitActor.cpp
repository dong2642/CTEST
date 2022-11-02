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


	// 물리 적용
	mMesh->SetSimulatePhysics(false);

	// 시뮬레이션 중 Hit event가 동작하도록 설정
	mMesh->SetNotifyRigidBodyCollision(true);

	// 함수 바인딩
	//this->OnActorHit.AddDynamic(this, &AHitActor::OnHit);

	//mMesh->OnComponentHit.AddDynamic(this, &AHitActor::OnComponentHit);
	

	// 오버랩 이벤트 등록
	mMesh->OnComponentBeginOverlap.AddDynamic(this, &AHitActor::OnOverlapBegin);
	mMesh->SetGenerateOverlapEvents(true);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// MyActorComponent.h 추가
	// 커스텀 컴포넌트를 만든다.
	UMyActorComponent* c_component = CreateDefaultSubobject<UMyActorComponent>(TEXT("CustomComponent"));


	// 컴포넌트 태그를 추가한다
	c_component->ComponentTags.Add(FName(TEXT("move")));

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 충돌 처리

	// 콜리전 타입 설정
	mMesh->SetCollisionObjectType(ECC_WorldDynamic);

	// 자신과의 충돌 방지
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

	// 형변환 사용할 때, 간단히 말해 형변환을 하려는 오브젝트가 형변환 대상 오브젝트와 같은지 검사 시도하는 것이다.
	/// Cast<변경하고자 하는 유형>(변경하고자 하는 대상); 

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


// "Overlap Begin: 메세지가 나오게 해보시오.
void AHitActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
}



// Called when the game starts or when spawned
void AHitActor::BeginPlay()
{
	Super::BeginPlay();
	
	// GetComponents() 모든 컴포넌트 가져오기

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
