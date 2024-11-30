#pragma once
#include "BossCharacter.h"

class AArmosKngiht_Control;
class APlayerCharacter;

enum class EBossState
{
	NONE,
	MOVE,
	KNOCKBACK,
	BERSERK_WAIT,
	BERSERK_MOVE,
	BERSERK_ATTACK,
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

	/** Bass Character 공통 메소드 */
	virtual void TakeDamage(int Damage, AActor* Character) override;
	virtual void Death() override;
	virtual void Fall() override;
	virtual FVector2D GetHitLocation() override;

	/** 상태(State) 메소드 */
	void Move(float DeltaTime);
	void Knockback(float DeltaTime);
	void BerserkWait(float DeltaTime);
	void BerserkMove(float DeltaTime);
	void BerserkAttack(float DeltaTime);

	/** 겟, 셋 메소드 */
	void SetTargetLocation(FVector2D Location)
	{
		this->TargetLocation = Location;
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
	void SetPlayerCharacter(APlayerCharacter* PlayerChracter)
	{
		TargetCharacter = PlayerChracter;
	}
	bool GetIsManage()
	{
		return IsManage;
	}

	/** Armos knight 메소드 */
	void ChangeState(EBossState BossState);
	void AddBossComponentLocation(FVector2D Location);
	void SetBossComponentLocation(FVector2D Location);
	void CheckAttackCollision();
	void PrintDebugInfo();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	AArmosKngiht_Control* Manager = nullptr;

	EBossState CurBossState = EBossState::NONE;
	EBossState PrevBossState = EBossState::NONE;
	APlayerCharacter* TargetCharacter = nullptr;

	FVector2D HitPower = FVector2D::ZERO;
	FVector2D TargetLocation = FVector2D::ZERO;
	FVector2D ComLoc = FVector2D::ZERO;
	FVector2D CurJumpPower = FVector2D::ZERO;

	float JumpSpeed = 100.0f;
	float CoolTime = 0.0f;

	int KnockBackCount = 0;
	int ManageIndex = 0;

	bool IsManage = true;
};

