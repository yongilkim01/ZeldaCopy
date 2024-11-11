#pragma once
#include "EnemyCharacter.h"

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

	void TakeDamage(int Damage = 10);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	int MaxHP = 100;
	int CurrentHP = 20;
};

