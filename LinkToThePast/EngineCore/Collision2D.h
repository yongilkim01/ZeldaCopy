#pragma once
#include "SceneComponent.h"
#include <set>

/**
 *	����
 */
class UCollision2D : public USceneComponent
{
public:
	friend class ULevel;

	/** ������, �Ҹ��� */
	UCollision2D();
	~UCollision2D();

	/** ��ü �� ���� ���� */
	UCollision2D(const UCollision2D& Other) = delete;
	UCollision2D(UCollision2D&& Other) noexcept = delete;
	UCollision2D& operator=(const UCollision2D& Other) = delete;
	UCollision2D& operator=(UCollision2D&& Other) noexcept = delete;

	/** ���� ������Ʈ ���� �޼ҵ� */
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;

	/** �ݸ��� ���� �޼ҵ� */
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
		// ��밡 100���̴�. 100�� 
		std::vector<AActor*> Result;
		Collision(static_cast<int>(OtherCollisionGroup), Result, NextDirection, -1);

		return Result;
	}
	void SetCollisionEnter(std::function<void(AActor*)> Function);
	void SetCollisionStay(std::function<void(AActor*)> Function);
	void SetCollisionEnd(std::function<void(AActor*)> Function);

	/** ��/�� */
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
