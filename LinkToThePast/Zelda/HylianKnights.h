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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Idle(float DeltaTime) override;
	virtual void Move(float DeltaTime) override;
	virtual void Attack(float DeltaTime) override;
	virtual void KnockBack(float DeltaTime) override;

private:


};

