#pragma once
#include "EnemyCharacter.h"

class USpriteRenderer;
class UCollision2D;

/**
 *	설명
 */
class AHylianKnight : public AEnemyCharacter
{
public:
	/** 생성자, 소멸자 */
	AHylianKnight();
	~AHylianKnight();

	/** 객체 값 복사 방지 */
	AHylianKnight(const AHylianKnight& _Other) = delete;
	AHylianKnight(AHylianKnight&& _Other) noexcept = delete;
	AHylianKnight& operator=(const AHylianKnight& _Other) = delete;
	AHylianKnight& operator=(AHylianKnight&& _Other) noexcept = delete;

	virtual void TakeDamage(int Damage = 10) override;

public:
	void ChangeMoveAnimation(FVector2D Direction);
	void ChangeHitAnimation(FVector2D Direction);
	void PrintDebugInfo();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Patrol(float DeltaTime) override;
	virtual void Attack(float DeltaTime) override;
	virtual void KnockBack(float DeltaTime) override;
	virtual void Trace(float DeltaTime) override;

private:
	int KnockBackCnt = 0;
	float Speed = 100.0f;

	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* CollisionComponent = nullptr;
	FVector2D CurrentDirection = FVector2D::ZERO;
};

