#pragma once
#include "EnemyCharacter.h"

class USpriteRenderer;

/**
 *	����
 */
class AHylianKnights : public AEnemyCharacter
{
public:
	/** ������, �Ҹ��� */
	AHylianKnights();
	~AHylianKnights();

	/** ��ü �� ���� ���� */
	AHylianKnights(const AHylianKnights& _Other) = delete;
	AHylianKnights(AHylianKnights&& _Other) noexcept = delete;
	AHylianKnights& operator=(const AHylianKnights& _Other) = delete;
	AHylianKnights& operator=(AHylianKnights&& _Other) noexcept = delete;

	virtual void TakeDamage(int Damage = 10) override;

public:
	void ChangeAnimation(FVector2D Direction);

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
	FVector2D CurrentDirection = FVector2D::ZERO;
};
