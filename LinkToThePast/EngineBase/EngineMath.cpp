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