#pragma once
#include "BossCharacter.h"
#include<list>

class AArmosKngiht;
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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	std::list<AArmosKngiht*> BossEnemies;

};

