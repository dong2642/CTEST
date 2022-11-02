// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTESTGameModeBase.h"
#include "MyDefaultPawn.h"
#include "MyPawn.h"
#include "MyActor.h"


ACTESTGameModeBase::ACTESTGameModeBase()
{
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}

void ACTESTGameModeBase::BeginPlay()
{
	AMyActor* ActorPtr = NewObject<AMyActor>(this, TEXT("TestUObject"));
	UObject* ObjPtr = ActorPtr;
	UClass* MyActorClass = AMyActor::StaticClass(); // AMyActor
	UClass* ObjectClass = UObject::StaticClass();   // UObject
	UClass* ActorPtrClass = ActorPtr->GetClass();	// AMyActor
	UClass* ObjPtrClass = ObjPtr->GetClass();		// AMyActor

	UE_LOG(LogClass, Error, TEXT("Name: %s"), *MyActorClass->GetName());
	UE_LOG(LogClass, Error, TEXT("Name: %s"), *ObjectClass->GetName());
	UE_LOG(LogClass, Error, TEXT("Name: %s"), *ActorPtrClass->GetName());
	UE_LOG(LogClass, Error, TEXT("Name: %s"), *ObjPtrClass->GetName());
}

// �𸮾� CDO�� ����ϱ� ���� ��. �̰��� ����ϸ� �ð��� ���ҽ��� �����Ѵ�.
// staticclass�� ������ Ÿ�Կ��� uclass Ÿ���� ������ ������ ���̸�, getclass�� ��Ÿ�ӿ��� ���� ��ü�� Ŭ������ ��ȸ�Ҷ� ���ȴ�.
// staticclass�� ������ Ÿ�Կ� �̹� ������ ���̴�. ������ �����Ͱ� ����Ű�� ���� ��ü�� Ÿ���� ��Ÿ�ӿ��� �޶��� �� �����Ƿ�,
// ���� ��ü�� Ŭ������ �����ϴ� getclass�� ���ϰ��� staticclass�� ���ϰ��� �ٸ� �� �ִ�.


// UCLASS�� CDO(Class Default Object)��� �ϴ� ���� UObject Ŭ������ �⺻ �ν��Ͻ��� ����Ǹ�, �� �ν��Ͻ��� ���� �Ҵ��
// ���� ������ �ʱ�ȭ�� �� Ŭ���� �����ڸ� ���� �� ���� �����˴ϴ�. CDO�� Ŭ������ �ٸ� ��� �ν��Ͻ��� ����Ǵ�
// ���ø� ������ �ϸ� �����ڴ� �ٽ� ȣ����� �ʽ��ϴ�.
