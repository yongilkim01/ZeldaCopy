#pragma once
#include "BossCharacter.h"

class AArmosKngiht_Control;

enum class EBossState
{
	NONE,
	MOVE,
	KNOCKBACK,
	BERSERK,
};

/**
 *	����
 */
class AArmosKnight : public ABossCharacter
{
public:
	/** ������, �Ҹ��� */
	AArmosKnight();
	~AArmosKnight();

	/** ��ü �� ���� ���� */
	AArmosKnight(const AArmosKnight& _Other) = delete;
	AArmosKnight(AArmosKnight&& _Other) noexcept = delete;
	AArmosKnight& operator=(const AArmosKnight& _Other) = delete;
	AArmosKnight& operator=(AArmosKnight&& _Other) noexcept = delete;

	/** Bass Character ���� �޼ҵ� */
	virtual void TakeDamage(int Damage, ABaseCharacter* Character) override;
	virtual void Death() override;

	/** ����(State) �޼ҵ� */
	void Move(float DeltaTime);
	void Knockback(float DeltaTime);

	/** ��, �� �޼ҵ� */
	void SetTargetLocation(FVector2D Location)
	{
		this->TargetLoc = Location;
	}
	void SetManager(AArmosKngiht_Control* Manager)
	{
		this->Manager = Manager;
	}
	void SetManageIndex(int Index)
	{
		this->ManageIndex = Index;
	}
	int GetManageIndex()
	{
		return this->ManageIndex;
	}

	/** Armos knight �޼ҵ� */
	void ChangeState(EBossState BossState);
	void PrintDebugInfo();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	AArmosKngiht_Control* Manager = nullptr;

	EBossState CurBossState = EBossState::NONE;
	ABaseCharacter* TargetCharacter = nullptr;

	FVector2D HitPower = FVector2D::ZERO;
	FVector2D TargetLoc = FVector2D::ZERO;
	FVector2D ComLoc = FVector2D::ZERO;
	FVector2D CurJumpPower = FVector2D::ZERO;

	float JumpSpeed = 100.0f;

	int KnockBackCount = 0;
	int ManageIndex = 0;
};

