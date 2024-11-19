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
	std::list<UActorComponent*>::iterator StartIter = Components.begin();
	std::list<UActorComponent*>::iterator EndIter = Components.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		UActorComponent* Component = *StartIter;

		if (Component != nullptr)
		{
			delete Component;
		}
	}

	Components.clear();
}

void AActor::Tick(float DeltaTime)
{
	if (IsDebug() == true)
	{
		FVector2D ActorLocation = GetActorLocation();
		FVector2D CameraLocation = GetWorld()->GetCameraLocation();

		FTransform Transform;
		Transform.Location = ActorLocation - CameraLocation;
		Transform.Scale = { 6, 6 };

		UEngineDebug::CoreDebugRender(Transform, UEngineDebug::EDebugPosType::Circle);
	}

	TimeEventer.Update(DeltaTime);

	std::list<class UActorComponent*>::iterator StartIter = Components.begin();
	std::list<class UActorComponent*>::iterator EndIter = Components.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (false == (*StartIter)->IsActive())
		{
			continue;
		}

		(*StartIter)->ComponentTick(DeltaTime);
	}
}

void AActor::ReleaseCheck(float DeltaTime)
{
	UObject::ReleaseCheck(DeltaTime);

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
		delete Component;
		StartIter = Components.erase(StartIter);
	}
}

void AActor::ReleaseTimeCheck(float DeltaTime)
{
	UObject::ReleaseTimeCheck(DeltaTime);

	std::list<UActorComponent*>::iterator StartIter = Components.begin();
	std::list<UActorComponent*>::iterator EndIter = Components.end();

	for (; StartIter != EndIter;)
	{
		UActorComponent* Component = *StartIter;

		if (false == Component->IsDestroy())
		{
			Component->ReleaseCheck(DeltaTime);
			++StartIter;
			continue;
		}
		delete Component;
		StartIter = Components.erase(StartIter);
	}
}
