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

	/** �ݸ��� ���� �׷��� �����ϴ� �޼ҵ� */
	template<typename EnumType>
	void SetCollisionGroup(EnumType CollisionGroup)
	{
		SetCollisionGroup(static_cast<int>(CollisionGroup));
	}
	void SetCollisionGroup(int CollisionGroup) { this->CollisionGroup = CollisionGroup; }

	template<typename EnumType>
	AActor* CollisionOnce(EnumType OtherCollisionGroup)
	{

		// ��밡 100���̴�. 100�� 
		std::vector<AActor*> Result;
		Collision(static_cast<int>(OtherCollisionGroup), Result, 1);

		if (true == Result.empty())
		{
			return nullptr;
		}

		return Result[0];
	}

	template<typename EnumType>
	std::vector<AActor*> CollisionAll(EnumType OtherCollisionGroup)
	{
		// ��밡 100���̴�. 100�� 
		std::vector<AActor*> Result;
		Collision(static_cast<int>(OtherCollisionGroup), Result, -1);

		return Result;
	}

	bool Collision(int OtherCollisionGroup, std::vector<AActor*>& ResultActors, unsigned int  Limite);

	void SetCollisionType(ECollisionType CollisionType)
	{
		this->CollisionType = CollisionType;
	}

	bool CollisionMap(UColor Color);

protected:

private:
	// �浹ü�� ������ �ణ �ǹ̰� �ٸ���.
	ECollisionType CollisionType = ECollisionType::Rect;
	int CollisionGroup = -1;
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
