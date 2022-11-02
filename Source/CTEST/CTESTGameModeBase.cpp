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

// 언리얼 CDO를 사용하기 위한 것. 이것을 사용하면 시간과 리소스를 절약한다.
// staticclass는 컴파일 타입에서 uclass 타입의 정보를 얻어오는 것이며, getclass는 런타임에서 실제 객체의 클래스를 조회할때 사용된다.
// staticclass는 컴파일 타입에 이미 정해진 것이다. 하지만 포인터가 가리키는 실제 객체의 타입은 런타임에서 달라질 수 있으므로,
// 실제 객체의 클래스를 리턴하는 getclass의 리턴값은 staticclass의 리턴값과 다를 수 있다.


// UCLASS는 CDO(Class Default Object)라고 하는 관련 UObject 클래스의 기본 인스턴스에 연결되며, 이 인스턴스는 먼저 할당된
// 다음 엔진이 초기화될 때 클래스 생성자를 통해 한 번만 생성됩니다. CDO는 클래스의 다른 모든 인스턴스가 복사되는
// 템플릿 역할을 하며 생성자는 다시 호출되지 않습니다.
