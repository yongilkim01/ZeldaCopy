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

		switch (CollisionType)
		{
		case ECollisionType::Point:
			break;
		case ECollisionType::Rect:
			UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Rect);
			break;
		case ECollisionType::Circle:
			UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Circle);
			break;
		case ECollisionType::Max:
			break;
		default:
			break;
		}
	}
}

bool UCollision2D::Collision(int OtherCollisionGroup, std::vector<AActor*>& ResultActors, unsigned int Limite)
{
	std::list<class UCollision2D*>& OtherCollisions = GetActor()->GetWorld()->Collisions[OtherCollisionGroup];

	std::list<class UCollision2D*>::iterator StartIter = OtherCollisions.begin();
	std::list<class UCollision2D*>::iterator EndIter = OtherCollisions.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		UCollision2D* ThisCollision = this;
		UCollision2D* TargetCollision = *StartIter;

		FTransform ThisTransform = ThisCollision->GetActorTransform();
		FTransform TargetTransform = TargetCollision->GetActorTransform();

		ECollisionType ThisCollisionType = ThisCollision->CollisionType;
		ECollisionType TargetCollisionType = TargetCollision->CollisionType;

		bool Result = FTransform::Collision(ThisCollisionType, ThisTransform, TargetCollisionType, TargetTransform);

		if (Result == true)
		{
			ResultActors.push_back(TargetCollision->GetActor());
			--Limite;

			if (Limite == 0)
			{
				return ResultActors.size() != 0;
			}
		}
	}
	return ResultActors.size() != 0;
}
