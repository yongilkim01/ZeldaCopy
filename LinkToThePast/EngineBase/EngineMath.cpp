#include "PreCompile.h"
#include "EngineMath.h"

const FVector2D FVector2D::ZERO = { 0, 0 };
const FVector2D FVector2D::LEFT = { -1, 0 };
const FVector2D FVector2D::RIGHT = { 1, 0 };
const FVector2D FVector2D::UP = { 0, -1 };
const FVector2D FVector2D::DOWN = { 0, 1 };

const FIntPoint FIntPoint::LEFT = { -1, 0 };
const FIntPoint FIntPoint::RIGHT = { 1, 0 };
const FIntPoint FIntPoint::UP = { 0, -1 };
const FIntPoint FIntPoint::DOWN = { 0, 1 };


const UColor UColor::WHITE = { 255, 255, 255, 0 };
const UColor UColor::BLACK = { 0, 0, 0, 0 };
const UColor UColor::PINK = { 255, 0, 255, 0 };
const UColor UColor::CYAN = { 0, 255, 255, 0 };
const UColor UColor::ORANGE = { 255, 150, 0, 0 };
const UColor UColor::YELLOW = { 255, 255, 0, 0 };

const UColor UColor::ROOM_UP = { 200, 0, 0, 0 };
const UColor UColor::ROOM_DOWN = { 0, 200, 0, 0 };

FIntPoint FVector2D::ConvertToPoint() const
{
	return { iX(), iY() };
}

FVector2D FVector2D::LerpClimp(FVector2D _StartLocation, FVector2D _TargetLocation, float _t)
{
	if (1.0F <= _t)
	{
		_t = 1.0F;
	}

	return FVector2D(_StartLocation.X + _t * (_TargetLocation.X - _StartLocation.X), _StartLocation.Y + _t * (_TargetLocation.Y - _StartLocation.Y));
}

std::function<bool(const FTransform&, const FTransform&)> FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)];

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RectToRect;
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Circle)][static_cast<int>(ECollisionType::Circle)] = FTransform::CircleToCircle;

	}
};

// 데이터 영역
CollisionFunctionInit Inst = CollisionFunctionInit();

bool FTransform::Collision(ECollisionType LeftCollisionType, 
						   const FTransform& LeftTransform, 
						   ECollisionType RightCollisionType,
						   const FTransform& RightTransform)
{
	return FTransform::AllCollisionFunction[static_cast<int>(LeftCollisionType)][static_cast<int>(RightCollisionType)](LeftTransform, RightTransform);
}

bool FTransform::RectToRect(const FTransform& LeftTransform, const FTransform& RightTransform)
{
	if (LeftTransform.CenterLeft() > RightTransform.CenterRight())
	{
		return false;
	}

	if (LeftTransform.CenterRight() < RightTransform.CenterLeft())
	{
		return false;
	}

	if (LeftTransform.CenterTop() > RightTransform.CenterBottom())
	{
		return false;
	}

	if (LeftTransform.CenterBottom() < RightTransform.CenterTop())
	{
		return false;
	}
	// 공식 만들면 된다.
	return true;
}

bool FTransform::CircleToCircle(const FTransform& LeftTrnasform, const FTransform& RightTransform)
{
	FVector2D Length = LeftTrnasform.Location - RightTransform.Location;

	// 트랜스폼을 원으로 봤을때 반지름은 x의 절반크기를 반지름으로 보겠습니다.

	// 두원의 반지름의 합이 벡터의 길이보다 크다면 
	if (Length.Length() < LeftTrnasform.Scale.hX() + RightTransform.Scale.hX())
	{
		return true;
	}

	return false;
}
