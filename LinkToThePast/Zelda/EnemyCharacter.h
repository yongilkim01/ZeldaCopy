#pragma once
#include <EngineCore/Actor.h>

class APlayerCharacter;

enum class EEnemyState
{
	Patrol,
	Move,
	Attack,
	KnockBack,
	Trace,
};

/**
 *	설명
 */
class AEnemyCharacter : public AActor
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

	virtual void TakeDamage(int Damage = 10);
	
	float CheckDistanceToPlayer();
	bool IsRangeToPlayer();
	void AddTurningLocation(FVector2D Location)
	{
		this->TurningLocations.push_back(Location);
	}
	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);

	EEnemyState GetCurEnemyState() { return this->CurEnemyState; }
	void SetCurEnemyState(EEnemyState EnemyState) { this->CurEnemyState = EnemyState; }
	void SetSpeed(float Speed) { this->Speed = Speed; }
	float GetSpeed() { return this->Speed; }

	void PrintEnemyDebugInfo();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Patrol(float DeltaTime) {};
	virtual void Attack(float DeltaTime) {};
	virtual void KnockBack(float DeltaTime) {};
	virtual void Trace(float DeltaTime) {};

	APlayerCharacter* PlayerCharacter = nullptr;
	std::vector<FVector2D> TurningLocations;
	FVector2D CurDir = FVector2D::ZERO;
	EEnemyState CurEnemyState = EEnemyState::Patrol;

	int CurTurningIndex = 0;

private:

	int MaxHP = 100;
	int CurrentHP = 20;
	float DetectionRange = 150.0f;
	float Speed = 100.0f;
};

