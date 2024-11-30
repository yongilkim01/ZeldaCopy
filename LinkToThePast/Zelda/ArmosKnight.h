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
	virtual void TakeDamage(int Damage, AActor* Character) override;
	virtual void Death() override;
	virtual void Fall() override;
	virtual FVector2D GetHitLocation() override;

	/** ����(State) �޼ҵ� */
	void Move(float DeltaTime);
	void Knockback(float DeltaTime);
	void BerserkWait(float DeltaTime);
	void BerserkMove(float DeltaTime);
	void BerserkAttack(float DeltaTime);

	/** ��, �� �޼ҵ� */
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

	/** Armos knight �޼ҵ� */
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

