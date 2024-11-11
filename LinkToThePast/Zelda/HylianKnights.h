#pragma once
#include "EnemyCharacter.h"

/**
 *	설명
 */
class AHylianKnights : public AEnemyCharacter
{
public:
	/** 생성자, 소멸자 */
	AHylianKnights();
	~AHylianKnights();

	/** 객체 값 복사 방지 */
	AHylianKnights(const AHylianKnights& _Other) = delete;
	AHylianKnights(AHylianKnights&& _Other) noexcept = delete;
	AHylianKnights& operator=(const AHylianKnights& _Other) = delete;
	AHylianKnights& operator=(AHylianKnights&& _Other) noexcept = delete;

	void TakeDamage(int Damage = 10);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	int MaxHP = 100;
	int CurrentHP = 20;
};

