// Fill out your copyright notice in the Description page of Project Settings.


#include "PointActor.h"
#include "MyDefaultPawn.h"

#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"


// Sets default values
APointActor::APointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// ���� ������Ʈ�� ���� SceneRoot�� ����
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// ����Ʈ�ڽ��� ����Ʈ�� Attachment
	PointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PointBox"));
	PointBox->SetupAttachment(SceneRoot);

	// ����Ʈ����Ʈ�� ����Ʈ�� Attachment
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLighName"));
	PointLight->SetupAttachment(SceneRoot);


	// ����Ʈ����Ʈ�� false�� ���·� ����
	PointLight->SetVisibility(false);
	

	// ������ �̺�Ʈ ���ε�
	PointBox->OnComponentBeginOverlap.AddDynamic(this, &APointActor::OnBeginOverlap);
	PointBox->OnComponentEndOverlap.AddDynamic(this, &APointActor::OnEndOverlap);
	



}

// Called when the game starts or when spawned
void APointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APointActor::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// OtherActor�� ����Ʈ������
	AMyDefaultPawn* actor = Cast<AMyDefaultPawn>(OtherActor);


	// �� ���Ͱ� firstcontroller�� ���� player����
	AMyDefaultPawn* player = Cast<AMyDefaultPawn>(GWorld->GetFirstPlayerController()->GetPawn());
		if (player != nullptr && actor == player)
		{
			PointLight->SetVisibility(true);
		}

}

void APointActor::OnEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyDefaultPawn* actor = Cast<AMyDefaultPawn>(OtherActor);

	AMyDefaultPawn* player = Cast<AMyDefaultPawn>(GWorld->GetFirstPlayerController()->GetPawn());
	if (player != nullptr && actor == player)
	{
		PointLight->SetVisibility(false);
	}

}

