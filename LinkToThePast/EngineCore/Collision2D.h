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
	// �浹ü�� ������ �ణ �ǹ̰� �ٸ���.
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
