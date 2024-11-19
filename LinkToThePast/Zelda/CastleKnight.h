#pragma once
#include "EnemyKnight.h"

/**
 *	설명
 */
class ACastleKnight : public AEnemyKnight
{
public:
	/** 생성자, 소멸자 */
	ACastleKnight();
	~ACastleKnight();

	/** 객체 값 복사 방지 */
	ACastleKnight(const ACastleKnight& _Other) = delete;
	ACastleKnight(ACastleKnight&& _Other) noexcept = delete;
	ACastleKnight& operator=(const ACastleKnight& _Other) = delete;
	ACastleKnight& operator=(ACastleKnight&& _Other) noexcept = delete;
	
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:

};

