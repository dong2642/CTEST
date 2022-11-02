
#include "MyPawn.h"
#include "MyActor.h"
#include "MyActorComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// ConstructorHelpers ������ ����� ���ø� �Դϴ�.
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		m_sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	// UMaterial
	static ConstructorHelpers::FObjectFinder<UMaterial>
		m_mat(TEXT("Material'/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean'"));

	UStaticMeshComponent* mMesh = CreateDefaultSubobject
		<UStaticMeshComponent>(TEXT("RootMeshComponent"));
	
	mMesh->SetStaticMesh(m_sphere.Object);
	mMesh->SetMaterial(0, m_mat.Object);

	RootComponent = mMesh;

	///////////////////////////////////////////////////////////////////////////////////////

	USpringArmComponent* CameraArm = CreateDefaultSubobject<USpringArmComponent>
		(TEXT("CameraSpringArm"));
	CameraArm->AttachTo(mMesh);
	CameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraArm->TargetArmLength = 300.f;
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 7.0f;
	CameraArm->bDoCollisionTest = false;
	UCameraComponent* FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	FollowCamera->AttachTo(CameraArm);
	

	mMesh->SetCollisionObjectType(ECC_Pawn);
		
	

	
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);

	PlayerInputComponent->BindAction("AddSphere", IE_Pressed, this, &AMyPawn::AddSphere);
	PlayerInputComponent->BindAction("SpawnActor", IE_Pressed, this, &AMyPawn::SpawnActor);
	PlayerInputComponent->BindAction("FireActor", IE_Pressed, this, &AMyPawn::FireActor);
	InputComponent->BindAction("Explosion", IE_Pressed, this, &AMyPawn::Explosion);
}

// #include "EngineUtils.h" ��� �߰�

// #include "Kismet/GameplayStatics.h"
// #include "Particles/ParticleSystem.h"
void AMyPawn::Explosion()
{
	UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));


	//// �������� ���� ã�� (UWrold ������Ʈ �ʿ�)
	for (TActorIterator<AMyActor> actor(GetWorld()); actor; ++actor)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor->GetActorTransform());
		actor->Destroy();
	}

	//// #include "GameFramework/Character.h" ��� �߰�
	for (AMyActor* actor2 : TActorRange<AMyActor>(GetWorld()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor2->GetActorTransform());
		actor2->Destroy();
	}
	
	
	// ���ͷ����͸� ����� for��
	for (TActorIterator<AMyActor> actor(GetWorld()); actor; ++actor)
		{
			AMyActor* myactor = Cast<AMyActor>(*actor);
			if (myactor)
				{
					myactor->bIsSmaller = true;
				}

		}



	// TObjectIterator
	// ��� ������Ʈ ������ �˻� �� �� �ֽ��ϴ�. Actor Iterator�� �޸� Object iterator�� Pre-PIE ���� Editor World���� 
	// ��ü�� �ݺ��� �� �ֽ��ϴ�. �̷� ���� ���ġ ���� ����� �߻��� �� �ֽ��ϴ�.
}


void AMyPawn::AddSphere()
{

	// CreateDefaultSubobject
	// Uobject�� �����ڿ����� ȣ��˴ϴ�. �������ٵ� ���������Ʈ Ŭ������ CDO �ν��Ͻ� �����մϴ�. ������ ������Ʈ��
	// �ش� ������Ʈ Ŭ������ �ν��Ͻ�ȭ�� �� �Ӽ��� �⺻ ������Ʈ�� �˴ϴ�.

	// NewObject<class>
	// ������ �ʱ�ȭ �� ���� ������Ʈ ������ ���� �Ϲ������� ����մϴ�. Uobject�� �����ڿ��� ������� �ʵ��� �մϴ�. 
	// UObject �����ڿ��� ȣ������ �ʾƾ� �մϴ�.

	UStaticMeshComponent* NewSphere = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), FName("AddSphere"));
	if (NewSphere)
	{
		UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
		UMaterial* mat = LoadObject<UMaterial>(nullptr, TEXT("Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"));

		NewSphere->AttachTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
		NewSphere->SetRelativeLocation(FVector(0, 0, 100));
		NewSphere->SetMaterial(0, mat);
		NewSphere->SetStaticMesh(mesh);

		// �� ������Ҹ� ����Ͽ� ������/������ ���¸� ����ϴ�. ���� �������� �ʴ� ��� �ܺ� Actor�� Components �迭���� �ڽ��� �߰��մϴ�.
		NewSphere->RegisterComponent();
	}

}

void AMyPawn::MoveForward(float Value)
{
	AddActorWorldOffset(FVector(Value, 0, 0));
}

void AMyPawn::MoveRight(float Value)
{
	AddActorWorldOffset(FVector(0, Value, 0));
}

void AMyPawn::SpawnActor()
{
	//FActorSpawnParameters() �⺻��������

	// �浹 �ϴ��� ����
	FActorSpawnParameters spawninfo = FActorSpawnParameters();
	spawninfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	// ���� ���� GWorld�� World�� �������� Ȯ���� �� �ִ� �븮 Ŭ�����Դϴ�.
	GWorld->SpawnActor<AMyActor>(GetActorLocation(), FRotator(0, 0, 0), spawninfo);
}

void AMyPawn::FireActor()
{
	FActorSpawnParameters spawninfo = FActorSpawnParameters();
	spawninfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GWorld->SpawnActor<AMyActor>(GetActorLocation(), FRotator(270, 0, 0), spawninfo);
}


//������Ʈ ����
//NewObject() - �ڵ� �����Ǵ� �̸����� �� �ν��Ͻ��� �����.

//�𸮾� ���������� UObject�� ������Ʈ ���������� �⺻���� �մϴ�.�� UClass�� UObject�� ������ CDO(Class Default Object)��� �Ҹ��� ����Ʈ �ν��Ͻ��� �����ϴ�.�� �ν��Ͻ��� ������ �ʱ�ȭ �ɶ� Ŭ���� �����ڸ� ���� ���ʷ� �� �ѹ� �Ҵ�˴ϴ�.���Ŀ� �����ڴ� ����� �ٽ� �ҷ����� �ʰ� ���ο� UObject�� ������ ���縦 ���� �մϴ�.
//�̰��� �ǹ��ϴ� ���� UObject �����ڴ� ��� ��Ÿ�� ������ ���� �Ҽ� ���ٴ� ���Դϴ�.
//���� Actor Component�� ���� ���� ������Ʈ���� �����ϰ� �ִ� ������Ʈ���, �̷��� ����Ʈ ������Ʈ���� ó���� �����Ǿ����� �մϴ�.

//CreateDefaultSubobject
//UObject�� �����ڿ����� ȣ���մϴ�.�������ٵ� ���������Ʈ Ŭ������ CDO �ν��Ͻ� �����մϴ�.������ ������Ʈ�� �ش� ������Ʈ Ŭ������ �ν��Ͻ�ȭ�� �� �Ӽ��� �⺻ ������Ʈ�� �˴ϴ�.


//NewObject< class >
//������ �ʱ�ȭ �� ���� ������Ʈ ������ ���� �Ϲ������� ����մϴ�.UObject�� �����ڿ��� ������� �ʵ��� �մϴ�.UObject �����ڿ��� ȣ������ �ʾƾ� �մϴ�.
//NewObject<class>�� ��ü �Ļ� Ŭ������ ���˴ϴ�(���ʹ� ���������� ���Ϳ��� ����ϸ� �� ��).�̰͵��� ������ ���� �������� �ʴ� �͵��Դϴ�.�װ͵��� ���� ������ ���̸�, �ı�, �޸� / ���� ó��, �� �ɷ� �鿡�� ���Ϳ� �ſ� �ٸ��� ó���˴ϴ�.��ġ�� ���ų� ������ ������ �������̱� ������ �̸� ����ϴ� Ŭ���� �ܿ��� ���ü��� �����ϴ�.

//SpawnActor< class >
//�������� location�� rotation ������ ���� ���͸� �����ϱ� ���� ���� ����Դϴ�.UObject �����ڿ��� ȣ������ �ʾƾ� �մϴ�.
//SpawnActor<class>�� Pawn, Controller�� ���� ���� �Ļ� Ŭ����, ������ ���迡 �����ϴ� ��� �Ϳ� ���˴ϴ�.���� ü��(Owner Chain)�� �����ϰ� ���Ϳ��� �߿������� �Ͱ� ���� �߰� �۾��� �����մϴ�.


// hitActor���� ������ �߰�
// TakeDamage(10, FDamageEvent(), NULL, this);
float AMyPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("TakeDamage"));

	

	return 0.0f;
}