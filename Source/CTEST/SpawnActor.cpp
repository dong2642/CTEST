// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"
#include "HitActor.h"

#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SetRootComponent(SpawnBox);
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	FTimerHandle CountdownTimerHandle;

	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ASpawnActor::Spawn, 0.3f, true);
}
// 타이머 0.3초마다 HitActor 스폰
// FVector RandomLocation = FMath::RandPointInBox(SpawnBox->Bounds.GetBox());
// HitActor를 생성하시오.


// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnActor::Spawn()
{
	FActorSpawnParameters spawninfo = FActorSpawnParameters();
	spawninfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector RandomLocation = FMath::RandPointInBox(SpawnBox->Bounds.GetBox());

	// 전역 변수 GWorld는 World에 엑세스를 확인할 수 있는 대리 클래스입니다.
	GWorld->SpawnActor<AHitActor>(RandomLocation, FRotator(0, 0, 0), spawninfo);

	
}

