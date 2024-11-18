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
const UColor UColor::ROOM_RIGHT = { 0, 0, 200, 0 };
const UColor UColor::ROOM_LEFT = { 200, 200, 0, 0 };

const UColor UColor::ROOM_UP_2F = { 225, 0, 0, 0 };
const UColor UColor::ROOM_DOWN_2F = { 0, 225, 0, 0 };
const UColor UColor::ROOM_RIGHT_2F = { 0, 0, 225, 0 };
const UColor UColor::ROOM_LEFT_2F = { 225, 225, 0, 0 };

const UColor UColor::ROOM_RIGHT_SMALL = { 0, 0, 240, 0 };
const UColor UColor::ROOM_LEFT_SMALL = { 240, 240, 0, 0 };

const UColor UColor::ROOM_UP_DIRECT = { 250, 0, 0, 0 };
const UColor UColor::ROOM_DOWN_DIRECT = { 0, 250, 0, 0 };
const UColor UColor::ROOM_RIGHT_DIRECT = { 0, 0, 250, 0 };
const UColor UColor::ROOM_LEFT_DIRECT = { 250, 250, 0, 0 };

const UColor UColor::FALL = { 44, 0, 0, 0 };

const UColor UColor::ROOM_UPSTAIRS = { 255, 100, 0, 0 };
const UColor UColor::ROOM_DOWNSTAIRS = { 255, 100, 100, 0 };

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
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Circle)] = FTransform::RectToCircle;
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Circle)][static_cast<int>(ECollisionType::Rect)] = FTransform::CircleToRect;
	}
};

// ������ ����
CollisionFunctionInit Inst = CollisionFunctionInit();

bool FTransform::Collision(ECollisionType LeftCollisionType, 
						   const FTransform& LeftTransform, 
						   ECollisionType RightCollisionType,
						   const FTransform& RightTransform)
{
	return FTransform::AllCollisionFunction[static_cast<int>(LeftCollisionType)][static_cast<int>(RightCollisionType)](LeftTransform, RightTransform);
}

bool FTransform::PointToRect(const FTransform& LeftTransform, const FTransform& RightTransform)
{
	FTransform LeftTrans = LeftTransform;
	LeftTrans.Scale = FVector2D::ZERO;

	return RectToRect(LeftTrans, RightTransform);
}

bool FTransform::PointToCircle(const FTransform& LeftTransform, const FTransform& RightTransform)
{
	FTransform LeftTrans = LeftTransform;
	LeftTrans.Scale = FVector2D::ZERO;

	return CircleToCircle(LeftTrans, RightTransform);
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
	// ���� ����� �ȴ�.
	return true;
}

bool FTransform::RectToCircle(const FTransform& LeftTransform, const FTransform& RightTransform)
{
	return CircleToRect(RightTransform, LeftTransform);
}


bool FTransform::CircleToRect(const FTransform& LeftTransform, const FTransform& RightTransform)
{
	FTransform WTransform = RightTransform;
	WTransform.Scale.X += LeftTransform.Scale.X;

	FTransform HTransform = RightTransform;
	HTransform.Scale.Y += LeftTransform.Scale.X;

	if (PointToRect(LeftTransform, WTransform) == true
		|| PointToRect(LeftTransform, HTransform) == true)
	{
		return true;
	}

	FVector2D ArrPoint[4];

	ArrPoint[0] = RightTransform.CenterLeftTop();
	ArrPoint[1] = RightTransform.CenterLeftBottom();
	ArrPoint[2] = RightTransform.CenterRightTop();
	ArrPoint[3] = RightTransform.CenterRightBottom();

	FTransform PointCircle;
	PointCircle.Scale = LeftTransform.Scale;

	for (size_t i = 0; i < 4; i++)
	{
		PointCircle.Location = ArrPoint[i];
		
		if (PointToCircle(LeftTransform, PointCircle) == true)
		{
			return true;
		}
	}

	return false;
}

bool FTransform::CircleToCircle(const FTransform& LeftTrnasform, const FTransform& RightTransform)
{
	FVector2D Length = LeftTrnasform.Location - RightTransform.Location;

	// Ʈ�������� ������ ������ �������� x�� ����ũ�⸦ ���������� ���ڽ��ϴ�.

	// �ο��� �������� ���� ������ ���̺��� ũ�ٸ� 
	if (Length.Length() < LeftTrnasform.Scale.hX() + RightTransform.Scale.hX())
	{
		return true;
	}

	return false;
}