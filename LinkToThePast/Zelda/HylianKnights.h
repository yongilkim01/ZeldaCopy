#pragma once
#include "EnemyKnight.h"

/**
 *	����
 */
class AHylianKnight : public AEnemyKnight
{
public:
	/** ������, �Ҹ��� */
	AHylianKnight();
	~AHylianKnight();

	/** ��ü �� ���� ���� */
	AHylianKnight(const AHylianKnight& _Other) = delete;
	AHylianKnight(AHylianKnight&& _Other) noexcept = delete;
	AHylianKnight& operator=(const AHylianKnight& _Other) = delete;
	AHylianKnight& operator=(AHylianKnight&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:


private:

};

