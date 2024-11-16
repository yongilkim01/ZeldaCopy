#pragma once
#include "BossCharacter.h"

enum class EBossState
{
	NONE,
	MOVE,
	KNOCKBACK
};

/**
 *	설명
 */
class AArmosKnight : public ABossCharacter
{
public:
	/** 생성자, 소멸자 */
	AArmosKnight();
	~AArmosKnight();

	/** 객체 값 복사 방지 */
	AArmosKnight(const AArmosKnight& _Other) = delete;
	AArmosKnight(AArmosKnight&& _Other) noexcept = delete;
	AArmosKnight& operator=(const AArmosKnight& _Other) = delete;
	AArmosKnight& operator=(AArmosKnight&& _Other) noexcept = delete;

	/** 상태(State) 메소드 */
	void Move(float DeltaTime);
	void Knockback(float DeltaTime);

	/** 겟, 셋 메소드 */
	void SetTargetLocation(FVector2D Location)
	{
		this->TargetLoc = Location;
	}
	void ChangeState(EBossState BossState)
	{
		this->CurBossState = BossState;
	}

	/** Boss Enemy 공통 메소드 */
	virtual void TakeDamage(int Damage, ABaseCharacter* Character) override;

	/** Armos knight 메소드 */
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

