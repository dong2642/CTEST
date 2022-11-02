// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefaultPawn.h"
#include "HitActor.h"

AMyDefaultPawn::AMyDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ�ѷ��� �����̼� ���� ����Ѵ�.
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
	// �������� ���� ����
	const FVector Start = GetActorLocation();
	const FVector Direction = GetActorRotation().Vector();
	const FVector End = Start + (Direction * 10000.0f);

	// ������� ���� ���� ����
	FHitResult Hit;
	// Ʈ���̽� �Ķ���� ����
	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
	// ������ �浹�� �����ؾ��ϴ��� ����
	TraceParams.bTraceComplex = true;
	// ������ ���� �޽� ������ ���� �ﰢ���� �ε����� ��ȯ���� ����
	TraceParams.bReturnFaceIndex = false;
	// �ڽ��� �����Ѵ�.
	TraceParams.AddIgnoredActor(this);

	// ����Ʈ���̽� ����׸� ǥ���ϴ� ���
	FName TraceTag = TEXT("None");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	TraceParams.TraceTag = TraceTag;


	// ����Ʈ���̽��� ���� �� Hit�� ����� GetActor��� TakeDamage, Hit�� ��� TakeDamage
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


