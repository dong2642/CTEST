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
		//ī��Ʈ �ٿ��� �Ϸ�Ǿ�����, Ÿ�̸Ӹ� ������ŵ�ϴ�.
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

//FString ���� ������ ���� �����Ϳ��� �ٲܼ� �ְ� ����� �������Ʈ���� �Ʒ� Ư������ ��ȯ�� ȣ�Ⱑ���ϰ� ����

void ATimerTest::CountdownHasFinished_Implementation()
{
	//Ư�� ������ ��ȯ�մϴ�.
	CountdownText->SetText(TextTest);

}
/*
* 
* 1�ʸ��� �Լ��� ȣ���ؼ�, 
* 3, 2, 1, GO!
* �ý�Ʈ ������ �� ó�� ǥ��
* GO! ���ķδ� ��ȭ ����
* 
* ��Ƽ���� ��Ʈ������ ��ȯ
FString::FromInt(FMath::Max(CountdownText, 0)
CountdownText->SetText(TEXT("GO!"));
GetWorldTimerManager().ClearTimer(Ŀ�����ڵ�);
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



