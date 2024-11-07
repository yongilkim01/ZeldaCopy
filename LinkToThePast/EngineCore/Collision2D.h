#pragma once
#include "SceneComponent.h"

/**
 *	설명
 */
class UCollision2D : public USceneComponent
{
public:
	// constrcuter destructer
	UCollision2D();
	~UCollision2D();

	// delete Function
	UCollision2D(const UCollision2D& _Other) = delete;
	UCollision2D(UCollision2D&& _Other) noexcept = delete;
	UCollision2D& operator=(const UCollision2D& _Other) = delete;
	UCollision2D& operator=(UCollision2D&& _Other) noexcept = delete;

	void BeginPlay() override;

	void ComponentTick(float _DeltaTime) override;

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
	template<typename EnumType>
	bool IsCollision(EnumType _OtherCollisionGroup)
	{
		return IsCollision(static_cast<int>(_OtherCollisionGroup));
	}
	template<typename EnumType>
	UCollision2D* CollisionOnce(EnumType _OtherCollisionGroup)
	{
		return CollisionOnce(static_cast<int>(_OtherCollisionGroup));
	}
	template<typename EnumType>
	bool Collision(EnumType _OtherCollisionGroup, std::vector<UCollision2D*>* _Result = nullptr)
	{
		return Collision(static_cast<int>(_OtherCollisionGroup), _Result);
	}

	void SetCollisionGroup(int CollisionGroup) { this->CollisionGroup = CollisionGroup; }
	bool IsCollision(int _OtherCollisionGroup);
	UCollision2D* Collision(int _OtherCollisionGroup);
	bool Collision(int _OtherCollisionGroup, std::vector<UCollision2D*>* _Result = nullptr);

protected:

private:
	// 충돌체의 오더는 약간 의미가 다르다.
	int CollisionGroup = -1;
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
