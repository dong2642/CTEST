// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerTest.h"
#include "Components/TextRenderComponent.h"



// Sets default values
ATimerTest::ATimerTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>
		(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;

	CountdownTime = 3;
	
} 

void ATimerTest::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}


void ATimerTest::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1)
	{
		//카운트 다운이 완료되었으니, 타이머를 중지시킵니다.
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

//FString 만들어서 끝나는 문구 에디터에서 바꿀수 있게 만들고 블루프린트에서 아래 특별문구 전환도 호출가능하게 변경

void ATimerTest::CountdownHasFinished_Implementation()
{
	//특별 문구로 전환합니다.
	CountdownText->SetText(TextTest);

}
/*
* 
* 1초마다 함수를 호출해서, 
* 3, 2, 1, GO!
* 택스트 랜더가 위 처럼 표현
* GO! 이후로는 변화 없음
* 
* 인티저를 스트링으로 변환
FString::FromInt(FMath::Max(CountdownText, 0)
CountdownText->SetText(TEXT("GO!"));
GetWorldTimerManager().ClearTimer(커스텀핸들);
*/


// Called when the game starts or when spawned
void ATimerTest::BeginPlay()
{
	Super::BeginPlay();

	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATimerTest::AdvanceTimer, 1.0f, true);


	
}

// Called every frame
void ATimerTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



