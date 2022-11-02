// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefaultPawn.h"
#include "HitActor.h"

AMyDefaultPawn::AMyDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러의 로테이션 값을 사용한다.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		m_sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	UStaticMeshComponent* Aim = CreateDefaultSubobject
		<UStaticMeshComponent>(TEXT("AimComponent"));

	Aim->SetStaticMesh(m_sphere.Object);
	Aim->SetRelativeLocation(FVector(30, 0, 0));
	Aim->SetRelativeScale3D(FVector(0.01f));

	Aim->AttachTo(RootComponent);
}

void AMyDefaultPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Explosion", IE_Pressed, this, &AMyDefaultPawn::Explosion);
}

void AMyDefaultPawn::Explosion()
{
	// 시작점과 끝점 설정
	const FVector Start = GetActorLocation();
	const FVector Direction = GetActorRotation().Vector();
	const FVector End = Start + (Direction * 10000.0f);

	// 결과값을 담을 지역 변수
	FHitResult Hit;
	// 트레이스 파라미터 설정
	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
	// 복잡한 충돌을 추적해야하는지 여부
	TraceParams.bTraceComplex = true;
	// 복잡한 정적 메쉬 추적을 위해 삼각형면 인덱스를 반환할지 여부
	TraceParams.bReturnFaceIndex = false;
	// 자신은 무시한다.
	TraceParams.AddIgnoredActor(this);

	// 라인트레이스 디버그를 표시하는 방법
	FName TraceTag = TEXT("None");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	TraceParams.TraceTag = TraceTag;


	// 라인트레이스를 쐈을 때 Hit한 대상이 GetActor라면 TakeDamage, Hit된 대상도 TakeDamage
	GWorld->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);

	if (Hit.GetActor())
	{
		Hit.GetActor()->TakeDamage(10, FDamageEvent(), NULL, this);
		

		if(Cast<AHitActor>(Hit.GetActor()))
		{
			Hit.GetActor()->Destroy();

		}
	}
}


