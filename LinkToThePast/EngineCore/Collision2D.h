#pragma once
#include "SceneComponent.h"

/**
 *	����
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
	// �浹ü�� ������ �ణ �ǹ̰� �ٸ���.
	int CollisionGroup = 0;
};

// �����е��� ������ �ϴ� ���
// enum class ContentsCollision
// {
//     PlayerBody,
//     PlayerAttack,
//	   MonsterBody,
//     MonsterAttack,
// }

// ��κ��� �浹 �Լ����� �̿� ���� �����ִ� �Լ��� �����ϰų� 
// ���������� GUI�� ������ ��� �մϴ�.
// void SetCollisionGroupCheck(ContentsCollision::PlayerBody, ContentsCollision::MonsterAttack);
