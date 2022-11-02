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
	
	// 하위 컴포넌트를 가질 SceneRoot를 생성
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// 포인트박스를 씬루트에 Attachment
	PointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PointBox"));
	PointBox->SetupAttachment(SceneRoot);

	// 포인트라이트를 씬루트에 Attachment
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLighName"));
	PointLight->SetupAttachment(SceneRoot);


	// 포인트라이트가 false인 상태로 시작
	PointLight->SetVisibility(false);
	

	// 오버랩 이벤트 바인딩
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
	// OtherActor가 디폴트폰인지
	AMyDefaultPawn* actor = Cast<AMyDefaultPawn>(OtherActor);


	// 그 엑터가 firstcontroller를 가진 player인지
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

