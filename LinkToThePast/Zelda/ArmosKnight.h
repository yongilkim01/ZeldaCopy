#pragma once
#include "BossCharacter.h"

enum class EBossState
{
	NONE,
	MOVE,
	KNOCKBACK
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

	/** ����(State) �޼ҵ� */
	void Move(float DeltaTime);
	void Knockback(float DeltaTime);

	/** ��, �� �޼ҵ� */
	void SetTargetLocation(FVector2D Location)
	{
		this->TargetLoc = Location;
	}
	void ChangeState(EBossState BossState)
	{
		this->CurBossState = BossState;
	}

	/** Boss Enemy ���� �޼ҵ� */
	virtual void TakeDamage(int Damage, ABaseCharacter* Character) override;

	/** Armos knight �޼ҵ� */
	void PrintDebugInfo();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	EBossState CurBossState = EBossState::NONE;
	ABaseCharacter* TargetCharacter = nullptr;

	FVector2D HitPower = FVector2D::ZERO;
	FVector2D TargetLoc = FVector2D::ZERO;
	FVector2D ComLoc = FVector2D::ZERO;
	FVector2D CurJumpPower = FVector2D::ZERO;

	float JumpSpeed = 100.0f;

	int KnockBackCount = 0;
};

