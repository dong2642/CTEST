
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
	
	// ConstructorHelpers 생성자 도우미 템플릿 입니다.
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

// #include "EngineUtils.h" 헤더 추가

// #include "Kismet/GameplayStatics.h"
// #include "Particles/ParticleSystem.h"
void AMyPawn::Explosion()
{
	UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));


	//// 유형으로 액터 찾기 (UWrold 오브젝트 필요)
	for (TActorIterator<AMyActor> actor(GetWorld()); actor; ++actor)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor->GetActorTransform());
		actor->Destroy();
	}

	//// #include "GameFramework/Character.h" 헤더 추가
	for (AMyActor* actor2 : TActorRange<AMyActor>(GetWorld()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor2->GetActorTransform());
		actor2->Destroy();
	}
	
	
	// 이터레이터를 사용한 for문
	for (TActorIterator<AMyActor> actor(GetWorld()); actor; ++actor)
		{
			AMyActor* myactor = Cast<AMyActor>(*actor);
			if (myactor)
				{
					myactor->bIsSmaller = true;
				}

		}



	// TObjectIterator
	// 모든 오브젝트 유형을 검색 할 수 있습니다. Actor Iterator와 달리 Object iterator는 Pre-PIE 세계 Editor World에서 
	// 객체를 반복할 수 있습니다. 이로 인해 얘기치 않은 결과가 발생할 수 있습니다.
}


void AMyPawn::AddSphere()
{

	// CreateDefaultSubobject
	// Uobject의 생성자에서만 호출됩니다. 무엇보다도 서브오브젝트 클래스의 CDO 인스턴스 생성합니다. 생성된 오브젝트는
	// 해당 오브젝트 클래스가 인스턴스화될 떄 속성의 기본 오브젝트가 됩니다.

	// NewObject<class>
	// 엔진이 초기화 된 이후 오브젝트 생성을 위해 일반적으로 사용합니다. Uobject의 생성자에서 사용하지 않도록 합니다. 
	// UObject 생성자에서 호출하지 않아야 합니다.

	UStaticMeshComponent* NewSphere = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), FName("AddSphere"));
	if (NewSphere)
	{
		UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
		UMaterial* mat = LoadObject<UMaterial>(nullptr, TEXT("Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"));

		NewSphere->AttachTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
		NewSphere->SetRelativeLocation(FVector(0, 0, 100));
		NewSphere->SetMaterial(0, mat);
		NewSphere->SetStaticMesh(mesh);

		// 이 구성요소를 등록하여 랜더링/물리적 상태를 만듭니다. 아직 존재하지 않는 경우 외부 Actor의 Components 배열에도 자신을 추가합니다.
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
	//FActorSpawnParameters() 기본생성정보

	// 충돌 하더라도 생성
	FActorSpawnParameters spawninfo = FActorSpawnParameters();
	spawninfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	// 전역 변수 GWorld는 World에 엑세스를 확인할 수 있는 대리 클래스입니다.
	GWorld->SpawnActor<AMyActor>(GetActorLocation(), FRotator(0, 0, 0), spawninfo);
}

void AMyPawn::FireActor()
{
	FActorSpawnParameters spawninfo = FActorSpawnParameters();
	spawninfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GWorld->SpawnActor<AMyActor>(GetActorLocation(), FRotator(270, 0, 0), spawninfo);
}


//오브젝트 생성
//NewObject() - 자동 생성되는 이름으로 새 인스턴스를 만든다.

//언리얼 엔진에서의 UObject는 오브젝트 프로토입을 기본으로 합니다.각 UClass는 UObject와 연관된 CDO(Class Default Object)라고 불리는 디폴트 인스턴스를 갖습니다.이 인스턴스는 엔진이 초기화 될때 클래스 생성자를 통해 최초로 단 한번 할당됩니다.이후에 생성자는 절대로 다시 불려지지 않고 새로운 UObject를 생성시 복사를 생성 합니다.
//이것이 의미하는 것은 UObject 생성자는 어떠한 런타임 로직을 포함 할수 없다는 것입니다.
//만약 Actor Component와 같은 서브 오브젝트들을 포함하고 있는 오브젝트라면, 이러한 디폴트 오브젝트들은 처음에 생성되어져야 합니다.

//CreateDefaultSubobject
//UObject의 생성자에서만 호출합니다.무엇보다도 서브오브젝트 클래스의 CDO 인스턴스 생성합니다.생성된 오브젝트는 해당 오브젝트 클래스가 인스턴스화될 때 속성의 기본 오브젝트가 됩니다.


//NewObject< class >
//엔진이 초기화 된 이후 오브젝트 생성을 위해 일반적으로 사용합니다.UObject의 생성자에서 사용하지 않도록 합니다.UObject 생성자에서 호출하지 않아야 합니다.
//NewObject<class>는 객체 파생 클래스에 사용됩니다(액터는 포함하지만 액터에는 사용하면 안 됨).이것들은 실제로 세상에 존재하지 않는 것들입니다.그것들은 단지 정보일 뿐이며, 파괴, 메모리 / 성능 처리, 그 능력 면에서 액터와 매우 다르게 처리됩니다.위치가 없거나 실제로 데이터 보유자이기 때문에 이를 사용하는 클래스 외에는 관련성이 없습니다.

//SpawnActor< class >
//레벨에서 location과 rotation 정보를 갖는 액터를 스폰하기 위한 편의 기능입니다.UObject 생성자에서 호출하지 않아야 합니다.
//SpawnActor<class>는 Pawn, Controller와 같은 액터 파생 클래스, 실제로 세계에 존재하는 모든 것에 사용됩니다.오너 체인(Owner Chain)을 설정하고 액터에게 중요해지는 것과 같은 추가 작업을 수행합니다.


// hitActor에서 데미지 추가
// TakeDamage(10, FDamageEvent(), NULL, this);
float AMyPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("TakeDamage"));

	

	return 0.0f;
}