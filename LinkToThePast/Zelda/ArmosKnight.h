#pragma once
#include "BossCharacter.h"

/**
 *	����
 */
class AArmosKnight : public ABossCharacter
{
public:
	/** ������, �Ҹ��� */
	AArmosKnight();
	~AArmosKnight();

	/** ��ü �� ���� ���� */
	AArmosKnight(const AArmosKnight& _Other) = delete;
	AArmosKnight(AArmosKnight&& _Other) noexcept = delete;
	AArmosKnight& operator=(const AArmosKnight& _Other) = delete;
	AArmosKnight& operator=(AArmosKnight&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

};

