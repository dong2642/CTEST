// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "MyDefaultPawn.generated.h"

/**
 * 
 */
UCLASS()
class CTEST_API AMyDefaultPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	AMyDefaultPawn();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Explosion();
	

};
