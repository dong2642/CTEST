// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerTest.generated.h"

UCLASS()
class CTEST_API ATimerTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UTextRenderComponent* CountdownText;

	UPROPERTY(EditAnywhere)
	int32 CountdownTime;

	void UpdateTimerDisplay();
	void AdvanceTimer();

	UPROPERTY(EditAnywhere)
		FString TextTest;

	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();

	FTimerHandle CountdownTimerHandle;

};
