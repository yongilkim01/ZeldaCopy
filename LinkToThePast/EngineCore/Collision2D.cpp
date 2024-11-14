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

bool UCollision2D::Collision(int _OtherCollisionGroup, std::vector<AActor*>& _Result, FVector2D _NextPos, unsigned int  _Limite)
{
	// 내가 xxxx 그룹이랑 충돌하는거죠.
	// 모든 충돌체를 한곳에 모아놓는게 Level
	UCollision2D* ThisCollision = this;

	if (false == ThisCollision->IsActive())
	{
		return false;
	}

	// 호출한 충돌체


	std::list<class UCollision2D*>& OtherCollisions = GetActor()->GetWorld()->Collisions[_OtherCollisionGroup];


	std::list<class UCollision2D*>::iterator StartIter = OtherCollisions.begin();
	std::list<class UCollision2D*>::iterator EndIter = OtherCollisions.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		UCollision2D* DestCollision = *StartIter;

		if (false == DestCollision->IsActive())
		{
			continue;
		}
		// 
		FTransform ThisTrans = ThisCollision->GetActorTransform();
		FTransform DestTrans = DestCollision->GetActorTransform();

		ThisTrans.Location += _NextPos;

		ECollisionType ThisType = ThisCollision->CollisionType;
		ECollisionType DestType = DestCollision->CollisionType;

		bool Result = FTransform::Collision(ThisType, ThisTrans, DestType, DestTrans);

		// 충돌 true
		if (true == Result)
		{
			_Result.push_back(DestCollision->GetActor());
			--_Limite;

			if (0 == _Limite)
			{
				return 0 != _Result.size();
			}
		}
	}

	return 0 != _Result.size();
}

bool UCollision2D::CollisionMap(UColor Color)
{
	return false;
}