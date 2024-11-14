#pragma once
#include "BossCharacter.h"
#include<list>

class AArmosKngiht;
/**
 *	����
 */
class AArmosKngiht_Control : public ABossCharacter
{
public:
	/** ������, �Ҹ��� */
	AArmosKngiht_Control();
	~AArmosKngiht_Control();

	/** ��ü �� ���� ���� */
	AArmosKngiht_Control(const AArmosKngiht_Control& _Other) = delete;
	AArmosKngiht_Control(AArmosKngiht_Control&& _Other) noexcept = delete;
	AArmosKngiht_Control& operator=(const AArmosKngiht_Control& _Other) = delete;
	AArmosKngiht_Control& operator=(AArmosKngiht_Control&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	std::list<AArmosKngiht*> BossEnemies;

};

