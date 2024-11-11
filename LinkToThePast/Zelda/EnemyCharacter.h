#pragma once
#include <EngineCore/Actor.h>

enum class EEnemyState
{
	Idle,
	Move,
	Attack,
	KnockBack,
};

/**
 *	����
 */
class AEnemyCharacter : public AActor
{
public:
	/** ������, �Ҹ��� */
	AEnemyCharacter();
	~AEnemyCharacter();

	/** ��ü �� ���� ���� */
	AEnemyCharacter(const AEnemyCharacter& _Other) = delete;
	AEnemyCharacter(AEnemyCharacter&& _Other) noexcept = delete;
	AEnemyCharacter& operator=(const AEnemyCharacter& _Other) = delete;
	AEnemyCharacter& operator=(AEnemyCharacter&& _Other) noexcept = delete;

	void TakeDamage(int Damage = 10);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Idle(float DeltaTime) {};
	virtual void Move(float DeltaTime) {};
	virtual void Attack(float DeltaTime) {};
	virtual void KnockBack(float DeltaTime) {};

private:
	int MaxHP = 100;
	int CurrentHP = 20;
	EEnemyState CurEnemyState = EEnemyState::Idle;
};

