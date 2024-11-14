#pragma once
#include "BossCharacter.h"
#include<list>

enum class EControlState
{
	SET,
	MOVE,
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
	bool CheckDistanceToTarget(FVector2D Location1, FVector2D Location2);
	void ChangeState(EControlState ControlState);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void Set(float DeltaTime);
	void Move(float DeltaTime);

	EControlState CurControlState = EControlState::SET;

	std::vector<AArmosKnight*> BossEnemies;
	std::vector<FVector2D> BossForces;

	float CurrentDegree = 30;
};

