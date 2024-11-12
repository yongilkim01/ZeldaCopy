#pragma once
#include <EngineCore/Actor.h>

class APlayerCharacter;
class AEffectEnemyDeath;

enum class EEnemyState
{
	Patrol,
	Attack,
	KnockBack,
	Trace,
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

	virtual void TakeDamage(int Damage = 10) {}
	
	float CheckDistanceToPlayer();
	bool IsRangeToPlayer();
	void AddTurningLocation(FVector2D Location)
	{
		this->TurningLocations.push_back(Location);
	}
	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);
	float GetDistanceToTargetLocation(FVector2D TargetLocation);

	EEnemyState GetCurEnemyState() { return this->CurEnemyState; }
	void SetCurEnemyState(EEnemyState EnemyState) { this->CurEnemyState = EnemyState; }
	void SetSpeed(float Speed) { this->Speed = Speed; }
	float GetSpeed() { return this->Speed; }
	bool GetDeathEffectAnimationIsEnd();

	void PrintEnemyDebugInfo();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Patrol(float DeltaTime) {};
	virtual void Attack(float DeltaTime) {};
	virtual void KnockBack(float DeltaTime) {};
	virtual void Trace(float DeltaTime) {};

	APlayerCharacter* PlayerCharacter = nullptr;
	AEffectEnemyDeath* DeathEffect = nullptr;

	std::vector<FVector2D> TurningLocations;
	FVector2D CurDir = FVector2D::ZERO;
	EEnemyState CurEnemyState = EEnemyState::Patrol;
	EEnemyState PrevEnemyState = EEnemyState::Patrol;

	int CurTurningIndex = 0;
	int MaxHP = 100;
	int CurrentHP = 40;
	float DetectionRange = 200.0f;
	float Speed = 80.0f;
	float AttackRange = 60.0f;

private:
};
