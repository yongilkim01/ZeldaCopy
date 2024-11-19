#pragma once
#include "EnemyKnight.h"

/**
 *	����
 */
class ACastleKnight : public AEnemyKnight
{
public:
	/** ������, �Ҹ��� */
	ACastleKnight();
	~ACastleKnight();

	/** ��ü �� ���� ���� */
	ACastleKnight(const ACastleKnight& _Other) = delete;
	ACastleKnight(ACastleKnight&& _Other) noexcept = delete;
	ACastleKnight& operator=(const ACastleKnight& _Other) = delete;
	ACastleKnight& operator=(ACastleKnight&& _Other) noexcept = delete;
	
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:

};

