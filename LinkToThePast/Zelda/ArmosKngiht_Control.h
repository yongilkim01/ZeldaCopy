#pragma once
#include "BossCharacter.h"
#include<list>


enum class EControlState
{
	SET,
	MOVE
};

class AArmosKnight;
/**
 *	설명
 */
class AArmosKngiht_Control : public ABossCharacter
{
public:
	/** 생성자, 소멸자 */
	AArmosKngiht_Control();
	~AArmosKngiht_Control();

	/** 객체 값 복사 방지 */
	AArmosKngiht_Control(const AArmosKngiht_Control& _Other) = delete;
	AArmosKngiht_Control(AArmosKngiht_Control&& _Other) noexcept = delete;
	AArmosKngiht_Control& operator=(const AArmosKngiht_Control& _Other) = delete;
	AArmosKngiht_Control& operator=(AArmosKngiht_Control&& _Other) noexcept = delete;

	FVector2D RotateToDegree(float Degree, FVector2D Location, float H);
	FVector2D RotateToRadian(float Radian, FVector2D Location, float H);
	void ChangeState(EControlState ControlState);
	void MoveForcesNextIndex();
	FVector2D GetRotateLocation(FVector2D Location, float Degree);
	void DestoryArmosKnight(AArmosKnight* ArmosKnight);
	
	void PrintDebugInfo();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void Set(float DeltaTime);
	void Move(float DeltaTime);

	EControlState CurControlState = EControlState::SET;

	std::list<AArmosKnight*> BossEnemies;
	std::vector<FVector2D> BossForces;

	float CurrentDegree = 20;
	float Speed = 200.0f;
	int PaddingIndex = 0;
	int CurPhase = 1;
	float PhaseTime = 0.0f;
	int MoveCallCount = 0;
	int AliveCount = 6;
};

