// Fill out your copyright notice in the Description page of Project Settings.

// 포함횟수와 관계없이 단 한 번 처리를 하고 그 이후에는 파일을 읽지 않고도 
// 컴파일러에 의해 처리가 되므로 결과적으로 빌드 시간을 절약할 수 있는 장점이 있다.
#pragma once


// 언리얼 오브잭트가 동작할 수 있는 최소 기능만 선언된 해더 파일(기본적인 타입, 연산 등)
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"
	
// 새로운 카테고리를 만들 때 사용하는 매크로
DECLARE_LOG_CATEGORY_EXTERN(LogMyActor, Log, All);


// 엔진이 클래스를 인식할  수 있도록 하며, 키워드 지정자와 함께 사용하여 엔진 내에서의 클래스 작동방식을 설정할 수 있습니다.
UCLASS()


// 모듈 밖에서 접근할 필요가 있는 함수와 클래스는 *_API 매크로를 통해 노출시켜야 합니다.
class CTEST_API AMyActor : public AActor
{
	// GENERATED_BODY 매크로는 인수를 받지 않으나, 클래스가 엔진에 필요한 인프라 스트럭쳐를 지원하도록 구성합니다.
	// 모든 UCLASS에 필수입니다.
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	bool bIsSmaller = false;

	void TimerTest();
	FTimerHandle TimerTestHandle;

};
