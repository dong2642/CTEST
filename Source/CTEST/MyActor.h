// Fill out your copyright notice in the Description page of Project Settings.

// ����Ƚ���� ������� �� �� �� ó���� �ϰ� �� ���Ŀ��� ������ ���� �ʰ� 
// �����Ϸ��� ���� ó���� �ǹǷ� ��������� ���� �ð��� ������ �� �ִ� ������ �ִ�.
#pragma once


// �𸮾� ������Ʈ�� ������ �� �ִ� �ּ� ��ɸ� ����� �ش� ����(�⺻���� Ÿ��, ���� ��)
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"
	
// ���ο� ī�װ��� ���� �� ����ϴ� ��ũ��
DECLARE_LOG_CATEGORY_EXTERN(LogMyActor, Log, All);


// ������ Ŭ������ �ν���  �� �ֵ��� �ϸ�, Ű���� �����ڿ� �Բ� ����Ͽ� ���� �������� Ŭ���� �۵������ ������ �� �ֽ��ϴ�.
UCLASS()


// ��� �ۿ��� ������ �ʿ䰡 �ִ� �Լ��� Ŭ������ *_API ��ũ�θ� ���� ������Ѿ� �մϴ�.
class CTEST_API AMyActor : public AActor
{
	// GENERATED_BODY ��ũ�δ� �μ��� ���� ������, Ŭ������ ������ �ʿ��� ������ ��Ʈ���ĸ� �����ϵ��� �����մϴ�.
	// ��� UCLASS�� �ʼ��Դϴ�.
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
