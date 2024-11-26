#pragma once
#include "EnemyCharacter.h"

#include <EnginePlatform/EngineSound.h>

class USpriteRenderer;
class UCollision2D;

/**
 *	설명
 */
class AEnemyKnight : public AEnemyCharacter
{
public:
	/** 생성자, 소멸자 */
	AEnemyKnight();
	~AEnemyKnight();

	/** 객체 값 복사 방지 */
	AEnemyKnight(const AEnemyKnight& _Other) = delete;
	AEnemyKnight(AEnemyKnight&& _Other) noexcept = delete;
	AEnemyKnight& operator=(const AEnemyKnight& _Other) = delete;
	AEnemyKnight& operator=(AEnemyKnight&& _Other) noexcept = delete;

	virtual void TakeDamage(int Damage, AActor* Character) override;
	virtual void Fall() override;

	/** Castle Knight 메소드 */
	void ChangeMoveAnimation(FVector2D Direction);
	void ChangeHitAnimation(FVector2D Direction);
	void EndFallAnimation();
	void PrintDebugInfo();

protected:
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 에너미 클래스 상속 메소드 */
	virtual void Patrol(float DeltaTime) override;
	virtual void Attack(float DeltaTime) override;
	virtual void KnockBack(float DeltaTime) override;
	virtual void Trace(float DeltaTime) override;

	UCollision2D* CollisionComponent = nullptr;
	FVector2D KnockBackDir = FVector2D::ZERO;

private:

	int KnockBackCnt = 0;
	float Range = 50.0f;
	USoundPlayer WalSoundPlayer;

};