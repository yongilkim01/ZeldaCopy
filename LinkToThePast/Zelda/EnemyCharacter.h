#pragma once
#include "BaseCharacter.h"

class APlayerCharacter;
class AEffectEnemyDeath;
class UCollision2D;

enum class EEnemyState
{
	Patrol,
	Attack,
	KnockBack,
	Trace,
};

/**
 *	설명
 */
class AEnemyCharacter : public ABaseCharacter
{
public:
	/** 생성자, 소멸자 */
	AEnemyCharacter();
	~AEnemyCharacter();

	/** 객체 값 복사 방지 */
	AEnemyCharacter(const AEnemyCharacter& _Other) = delete;
	AEnemyCharacter(AEnemyCharacter&& _Other) noexcept = delete;
	AEnemyCharacter& operator=(const AEnemyCharacter& _Other) = delete;
	AEnemyCharacter& operator=(AEnemyCharacter&& _Other) noexcept = delete;
	
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
	bool GetDeathEffectAnimationIsEnd();

protected:
	/** 액터 가상함수 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Patrol(float DeltaTime) {};
	virtual void Attack(float DeltaTime) {};
	virtual void KnockBack(float DeltaTime) {};
	virtual void Trace(float DeltaTime) {};

	APlayerCharacter* PlayerCharacter = nullptr;
	AEffectEnemyDeath* DeathEffect = nullptr;

	std::vector<FVector2D> TurningLocations;
	std::vector<UCollision2D*> AttackCollisions;

	EEnemyState CurEnemyState = EEnemyState::Patrol;
	EEnemyState PrevEnemyState = EEnemyState::Patrol;

	int CurTurningIndex = 0;
	float DetectionRange = 200.0f;
	float AttackRange = 80.0f;
	float AttackCoolTime = 0.0f;

	bool IsAttack = false;

private:
};

