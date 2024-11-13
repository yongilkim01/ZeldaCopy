#pragma once
// FVector로 통일하겠습니다.
// FVector2D xy
// FVector3D xyz
// FVector4D xyzw
// FVector4D == FVector;

class FVector2D
{
public:
	float X = 0.0f;
	float Y = 0;

	static const FVector2D ZERO;
	static const FVector2D LEFT;
	static const FVector2D RIGHT;
	static const FVector2D UP;
	static const FVector2D DOWN;

	FVector2D()
	{

	}

	FVector2D(float _X, float _Y) : X(_X), Y(_Y)
	{

	}

	FVector2D(int _X, int _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
	{

	}

	FVector2D(long _X, long _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
	{

	}

	int iX() const
	{
		return static_cast<int>(X);
	}

	int iY() const
	{
		return static_cast<int>(Y);
	}

	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}

	// X든 Y든 0이있으면 터트리는 함수.
	bool IsZeroed() const
	{
		return X == 0.0f || Y == 0.0f;
	}

	FVector2D Half() const
	{
		return { X * 0.5f, Y * 0.5f };
	}

	float Length() const
	{
		return sqrtf(X * X + Y * Y);
	}

	float DistanceTo(const FVector2D& Other) const {
		return std::sqrt((X - Other.X) * (X - Other.X) + (Y - Other.Y) * (Y - Other.Y));
	}

	class FIntPoint ConvertToPoint() const;

	void Normalize()
	{
		float Len = Length();
		if (0.0f < Len && false == isnan(Len))
		{
			X = X / Len;
			Y = Y / Len;
		}
		return;
	}


	void Normal()
	{
		if (X > 0)
		{
			X = 1;
		}
		if (Y > 0)
		{
			Y = 1;
		}
		return;
	}

	float Dot(const FVector2D& Other) const
	{
		return X * Other.X + Y * Other.Y;
	}

	FVector2D operator*(float Value) const
	{
		FVector2D Result;
		Result.X = X * Value;
		Result.Y = Y * Value;
		return Result;
	}

	FVector2D operator+(FVector2D _Other) const
	{
		FVector2D Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}


	FVector2D operator-(FVector2D _Other) const
	{
		FVector2D Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}

	FVector2D operator-() const
	{
		FVector2D Result;
		Result.X = -X;
		Result.Y = -Y;
		return Result;
	}

	FVector2D& operator-=(FVector2D _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		return *this;
	}


	FVector2D operator/(int _Value) const
	{
		FVector2D Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}

	FVector2D operator/(const FVector2D& Other) const
	{
		FVector2D Result;
		Result.X = X / Other.X;
		Result.Y = Y / Other.Y;
		return Result;
	}

	// ture가 나오는 
	bool operator==(FVector2D _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	// float은 비교가 굉장히 위험
	// const가 붙은 함수에서는 const가 붙은 함수 호출할수 없다.
	bool EqualToInt(FVector2D _Other) const
	{
		// const FVector* const Ptr;
		// this = nullptr;
		return iX() == _Other.iX() && iY() == _Other.iY();
	}

	//bool Compare(FVector2D _Other, float _limite = 0.0f) const
	//{
	//	return X == _Other.X && Y == _Other.Y;
	//}

	FVector2D& operator+=(FVector2D _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}

	static FVector2D LerpClimp(FVector2D _StartLocation, FVector2D _TargetLocation, float _t);

	std::string ToString()
	{
		std::string Stream;

		Stream += "X : [";
		Stream += std::to_string(X);
		Stream += "] Y : [";
		Stream += std::to_string(Y);
		Stream += "]";
		return Stream;
	}
};

enum class ECollisionType
{
	Point,
	Rect,
	Circle, // 타원이 아닌 정방원 
	Max

	//AABB,
	//OBB,
};

// 대부분 오브젝트에서 크기와 위치는 한쌍입니다.
// 그래서 그 2가지를 모두 묶는 자료형을 만들어서 그걸 써요.
class FTransform
{
private:
	friend class CollisionFunctionInit;

	static std::function<bool(const FTransform&, const FTransform&)> 
		AllCollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)];

public:
	static bool Collision(
		ECollisionType LeftCollisionType,
		const FTransform& LeftTransform,
		ECollisionType RightCollisionType,
		const FTransform& RightTransform);

	static bool RectToRect(const FTransform& LeftTransform, const FTransform& RightTransform);
	static bool CircleToCircle(const FTransform& LeftTrnasform, const FTransform& RightTransform);

	FVector2D Scale = FVector2D::ZERO;
	FVector2D Location = FVector2D::ZERO;

	FVector2D CenterLeftTop() const
	{
		return Location - Scale.Half();
	}

	float CenterLeft() const
	{
		return Location.X - Scale.hX();
	}

	float CenterTop() const
	{
		return Location.Y - Scale.hY();
	}

	FVector2D CenterRightBottom() const
	{
		return Location + Scale.Half();
	}

	float CenterRight() const
	{
		return Location.X + Scale.hX();
	}

	float CenterBottom() const
	{
		return Location.Y + Scale.hY();
	}
};

class FIntPoint
{
public:
	int X = 0;
	int Y = 0;

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

	FIntPoint()
	{

	}

	FIntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{

	}

	FIntPoint operator+(FIntPoint _Other) const
	{
		FIntPoint Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FIntPoint operator/(int _Value) const
	{
		FIntPoint Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	bool operator==(FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FIntPoint& operator+=(FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}


};

class EngineMath
{
public:
	static FVector2D Lerp(FVector2D StartLocation, FVector2D EndLocation, float Distance)
	{
		return { StartLocation.X + Distance * (EndLocation.X - StartLocation.X), StartLocation.Y + Distance * (EndLocation.Y - StartLocation.Y) };

	}

	static float Sqrt(float _Value)
	{
		return ::sqrtf(_Value);
	}

	static int Abs(int Value)
	{
		return std::abs(Value);
	}

	static float Abs(float Value)
	{
		return std::abs(Value);
	}

	template <typename DataType>
	DataType ClampMax(DataType value, DataType maxValue)
	{
		return (value > maxValue) ? maxValue : value;
	}
	template <typename DataType>
	DataType ClampMin(DataType value, DataType minValue)
	{
		return (value < minValue) ? minValue : value;
	}
	template <typename DataType>
	static DataType Clamp(DataType value, DataType minValue, DataType maxValue)
	{
		if (value < minValue)
			return minValue;
		else if (value > maxValue)
			return maxValue;
		else
			return value;
	}
};



class UColor
{
public:
	static const UColor WHITE;
	static const UColor BLACK;
	static const UColor PINK;
	static const UColor CYAN;
	static const UColor BLUE;
	static const UColor YELLOW;
	static const UColor ORANGE;


	static const UColor ROOM_UP;
	static const UColor ROOM_DOWN;
	static const UColor ROOM_RIGHT;
	static const UColor ROOM_LEFT;

	static const UColor ROOM_UP_2F;
	static const UColor ROOM_DOWN_2F;
	static const UColor ROOM_RIGHT_2F;
	static const UColor ROOM_LEFT_2F;

	static const UColor ROOM_UP_DIRECT;
	static const UColor ROOM_DOWN_DIRECT;
	static const UColor ROOM_RIGHT_DIRECT;
	static const UColor ROOM_LEFT_DIRECT;

	static const UColor ROOM_UPSTAIRS;
	static const UColor ROOM_DOWNSTAIRS;

	static const UColor FALL;

	union
	{
		int Color;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
	};

	UColor(unsigned long _Value)
		:Color(_Value)
	{

	}

	bool operator==(const UColor& _Other)
	{
		return R == _Other.R && G == _Other.G && B == _Other.B;
	}


	UColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}

	std::string ToString()
	{
		return "R: " + std::to_string(R) + ", G: " + std::to_string(G) + ", B: " + std::to_string(B);
	}
};