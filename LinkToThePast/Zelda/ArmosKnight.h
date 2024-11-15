#pragma once
#include "BossCharacter.h"

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

	void SetTargetLocation(FVector2D Location)
	{
		this->TargetLoc = Location;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FVector2D HitPower = FVector2D::ZERO;
	FVector2D TargetLoc = FVector2D::ZERO;

	FVector2D ComLoc = FVector2D::ZERO;

	FVector2D CurJumpPower;
	float JumpSpeed = 100.0f;
	float CurDir = -1.0f;

};

