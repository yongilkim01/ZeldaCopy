#include "PreCompile.h"
#include "Actor.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

#include "EngineSprite.h"
#include "ImageManager.h"
#include "ActorComponent.h"
#include "EngineCoreDebug.h"

std::list<UActorComponent*> AActor::ComponentList;

void AActor::ComponentBeginPlay()
{
	std::list<UActorComponent*>::iterator StartIter = ComponentList.begin();
	std::list<UActorComponent*>::iterator EndIter = ComponentList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		UActorComponent* CurActor = *StartIter;
		CurActor->BeginPlay();
	}
	ComponentList.clear();
}

AActor::AActor()
{
}

AActor::~AActor()
{
	// 컴포넌트의 생성주기는 액터의 생명주기와 같다고 한다.
	std::list<UActorComponent*>::iterator StartIter = Components.begin();
	std::list<UActorComponent*>::iterator EndIter = Components.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		UActorComponent* Component = *StartIter;

		if (nullptr != Component)
		{
			delete Component;
		}
	}

	Components.clear();
}

void AActor::Tick(float _DeltaTime)
{
	if (true == IsDebug)
	{
		FVector2D Pos = GetActorLocation();
		FVector2D CameraPos = GetWorld()->GetCameraPos();
		UEngineDebug::CoreDebugPos(Pos - CameraPos, UEngineDebug::EDebugPosType::Circle);
		//UEngineDebug::Core
	}

	std::list<class UActorComponent*>::iterator StartIter = Components.begin();
	std::list<class UActorComponent*>::iterator EndIter = Components.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->ComponentTick(_DeltaTime);
	}
}

void AActor::ReleaseCheck(float DeltaTime)
{
	UObject::ReleaseCheck(DeltaTime);
	// 컴포넌트의 생성주기는 액터의 생명주기와 같다고 한다.
	std::list<UActorComponent*>::iterator StartIter = Components.begin();
	std::list<UActorComponent*>::iterator EndIter = Components.end();
	for (; StartIter != EndIter; )
	{
		UActorComponent* Component = *StartIter;
		if (false == Component->IsDestroy())
		{
			Component->ReleaseCheck(DeltaTime);
			++StartIter;
			continue;
		}
		// 액터는 죽을 컴포넌트가 있으면 진짜 죽
		delete Component;
		StartIter = Components.erase(StartIter);
	}
}