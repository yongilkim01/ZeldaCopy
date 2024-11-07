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

protected:

private:
	// 충돌체의 오더는 약간 의미가 다르다.
	int CollisionGroup = 0;
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
