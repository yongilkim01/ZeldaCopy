#pragma once
#include "SceneComponent.h"
#include <set>

/**
 *	설명
 */
class UCollision2D : public USceneComponent
{
public:
	friend class ULevel;

	/** 생성자, 소멸자 */
	UCollision2D();
	~UCollision2D();

	/** 객체 값 복사 방지 */
	UCollision2D(const UCollision2D& Other) = delete;
	UCollision2D(UCollision2D&& Other) noexcept = delete;
	UCollision2D& operator=(const UCollision2D& Other) = delete;
	UCollision2D& operator=(UCollision2D&& Other) noexcept = delete;

	/** 액터 컴포넌트 공동 메소드 */
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;

	/** 콜리전 전용 메소드 */
	bool Collision(int OtherCollisionGroup,
				   std::vector<AActor*>& Result,
				   FVector2D NexrDirection,
				   unsigned int  Limite);
	template<typename EnumType>
	AActor* CollisionOnce(EnumType OtherCollisionGroup, FVector2D NextLocation = FVector2D::ZERO)
	{
		std::vector<AActor*> Result;
		Collision(static_cast<int>(OtherCollisionGroup), Result, NextLocation, 1);

		if (true == Result.empty())
		{
			return nullptr;
		}

		return Result[0];
	}
	template<typename EnumType>
	std::vector<AActor*> CollisionAll(EnumType OtherCollisionGroup, FVector2D NextDirection = FVector2D::ZERO)
	{
		// 상대가 100개이다. 100개 
		std::vector<AActor*> Result;
		Collision(static_cast<int>(OtherCollisionGroup), Result, NextDirection, -1);

		return Result;
	}
	void SetCollisionEnter(std::function<void(AActor*)> Function);
	void SetCollisionStay(std::function<void(AActor*)> Function);
	void SetCollisionEnd(std::function<void(AActor*)> Function);

	/** 겟/셋 */
	template<typename EnumType>
	EnumType GetGroup()
	{
		return static_cast<EnumType>(CollisionGroup);
	}
	int GetGroup()
	{
		return CollisionGroup;
	}
	template<typename EnumType>
	void SetCollisionGroup(EnumType CollisionGroup)
	{
		SetCollisionGroup(static_cast<int>(CollisionGroup));
	}
	void SetCollisionGroup(int CollisionGroup)
	{
		this->CollisionGroup = CollisionGroup;
	}
	ECollisionType GetCollisionType()
	{
		return CollisionType;
	}
	void SetCollisionType(ECollisionType CollisionType)
	{
		this->CollisionType = CollisionType;
	}

protected:

private:
	void CollisionEventCheck(class UCollision2D* Other);

	ECollisionType CollisionType = ECollisionType::Rect;
	int CollisionGroup = -1;

	std::set<UCollision2D*> CollisionCheckSet;

	std::function<void(AActor*)> Enter;
	std::function<void(AActor*)> Stay;
	std::function<void(AActor*)> End;

};

// 여러분들이 만들어야 하는 기능
// enum class ContentsCollision
// {
//     PlayerBody,
//     PlayerAttack,
//	   MonsterBody,
//     MonsterAttack,
// }

// 대부분의 충돌 함수들이 이와 같은 엮어주는 함수를 지원하거나 
// 엔진수준의 GUI로 지원해 줘야 합니다.
// void SetCollisionGroupCheck(ContentsCollision::PlayerBody, ContentsCollision::MonsterAttack);
