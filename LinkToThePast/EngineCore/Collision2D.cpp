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

	if (0 > CollisionGroup)
	{
		MSGASSERT("충돌 그룹은 음수가 될수 없습니다.");
		return;
	}

	Level->PushCollision(this);

	if (nullptr != Enter || nullptr != Stay || nullptr != End)
	{
		Level->PushCheckCollision(this);
	}
}

void UCollision2D::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);

	if (true == IsDebug() || true == GetActor()->IsDebug())
	{
		// 현재 액터의 위치와 카메라 위치를 사용
		FTransform ActorTransform = GetActorTransform();
		FVector2D CameraPos = GetActor()->GetWorld()->GetCameraLocation();

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

bool UCollision2D::Collision(int OtherCollisionGroup, 
							 std::vector<AActor*>& Result,
							 FVector2D NextLocation, 
							 unsigned int  Limite)
{
	UCollision2D* ThisCollision = this;

	if (false == ThisCollision->IsActive())
	{
		return false;
	}

	std::list<class UCollision2D*>& OtherCollisions = GetActor()->GetWorld()->Collisions[OtherCollisionGroup];


	std::list<class UCollision2D*>::iterator StartIter = OtherCollisions.begin();
	std::list<class UCollision2D*>::iterator EndIter = OtherCollisions.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		UCollision2D* DestCollision = *StartIter;

		if (ThisCollision == DestCollision)
		{
			continue;
		}

		if (false == DestCollision->IsActive())
		{
			continue;
		}

		FTransform ThisTrans = ThisCollision->GetActorTransform();
		FTransform DestTrans = DestCollision->GetActorTransform();

		ThisTrans.Location += NextLocation;

		ECollisionType ThisType = ThisCollision->CollisionType;
		ECollisionType DestType = DestCollision->CollisionType;

		bool IsCollision = FTransform::Collision(ThisType, ThisTrans, DestType, DestTrans);

		if (true == IsCollision)
		{
			Result.push_back(DestCollision->GetActor());
			--Limite;

			if (0 == Limite)
			{
				return 0 != Result.size();
			}
		}
	}

	return 0 != Result.size();
}

void UCollision2D::SetCollisionEnter(std::function<void(AActor*)> Function)
{
	Enter = Function;

	ULevel* CurLevel = GetActor()->GetWorld();

	if (nullptr != CurLevel)
	{
		CurLevel->PushCheckCollision(this);
	}
}

void UCollision2D::SetCollisionStay(std::function<void(AActor*)> Function)
{
	Stay = Function;

	ULevel* CurLevel = GetActor()->GetWorld();

	if (nullptr != CurLevel)
	{
		CurLevel->PushCheckCollision(this);
	}
}

void UCollision2D::SetCollisionEnd(std::function<void(AActor*)> Function)
{
	End = Function;

	ULevel* CurLevel = GetActor()->GetWorld();

	if (nullptr != CurLevel)
	{
		CurLevel->PushCheckCollision(this);
	}
}

void UCollision2D::CollisionEventCheck(UCollision2D* Other)
{
	UCollision2D* ThisCollision = this;
	UCollision2D* DestCollision = Other;

	FTransform ThisTransform = ThisCollision->GetActorTransform();
	FTransform DestTransform = DestCollision->GetActorTransform();

	ECollisionType ThisCollisionType = ThisCollision->GetCollisionType();
	ECollisionType DestCollisionType = DestCollision->GetCollisionType();

	bool IsCollision = FTransform::Collision(ThisCollisionType, ThisTransform,
											 DestCollisionType, DestTransform);

	// 콜리전이 일어났는지 확인
	if (true == IsCollision)
	{
		// 콜리전이 일어났고 현재 체크하고 있는지 검사
		if (false == CollisionCheckSet.contains(DestCollision))
		{
			// 체크하지 않고 있다면 처음 들어온거므로 Enter에 삽입
			if (nullptr != Enter)
			{
				Enter(DestCollision->GetActor());
			}
			CollisionCheckSet.insert(DestCollision);
		}
		else
		{
			if (nullptr != Stay)
			{
				Stay(DestCollision->GetActor());
			}
		}
	}
	else
	{
		// 충돌은 하지 않았지만 충돌한 기록은 가지고 있는지 검사
		if (true == CollisionCheckSet.contains(DestCollision))
		{
			if (nullptr != End)
			{
				End(DestCollision->GetActor());
			}
			CollisionCheckSet.erase(DestCollision);
		}

	}
}