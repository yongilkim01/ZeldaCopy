#pragma once
#include "EnemyKnight.h"

/**
 *	설명
 */
class AHylianKnight : public AEnemyKnight
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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:


private:

};

