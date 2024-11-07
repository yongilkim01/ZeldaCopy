#include "PreCompile.h"
#include "Collision2D.h"
#include <EngineCore/EngineCoreDebug.h>

UCollision2D::UCollision2D()
{
}

UCollision2D::~UCollision2D()
{
}

void UCollision2D::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

	if (CollisionGroup < 0)
	{
		MSGASSERT("충돌 그룹은 음수가 될수 없습니다.");
		return;
	}

	Level->PushCollision(this);
}

void UCollision2D::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);

	if (true == IsDebug() || true == GetActor()->IsDebug())
	{

		FTransform ActorTransform = GetActorTransform();
		FVector2D CameraPos = GetActor()->GetWorld()->GetCameraPos();

		ActorTransform.Location -= CameraPos;

		UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Rect);
	}
}


bool UCollision2D::IsCollision(int _OtherCollisionGroup)
{
	return false;
}

UCollision2D* UCollision2D::Collision(int _OtherCollisionGroup)
{
	return nullptr;
}

bool UCollision2D::Collision(int _OtherCollisionGroup, std::vector<UCollision2D*>* _Result)
{
	return false;
}
