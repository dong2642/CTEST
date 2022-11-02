// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (FollowTarget)
	{
		// 현재에서 대상으로 백터를 보간합니다. 대상까지의 거리에 따라 조정되므로 시작 속도가 빠르고 쉽게 빠져나갑니다.
		FVector move = FMath::VInterpTo(GetOwner()->GetActorLocation(), FollowTarget->GetActorLocation(), DeltaTime, FollowSpeed);
		GetOwner()->SetActorLocation(move, true);
	}
}

void UMyActorComponent::SetFollowTarget(AActor* target, float speed)
{
	FollowTarget = target;
	FollowSpeed = speed;
}

