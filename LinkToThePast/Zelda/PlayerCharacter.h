#pragma once
#include <EngineCore/ImageManager.h>
#include <EngineCore/Collision2D.h>
#include <EnginePlatform/EngineSound.h>

#include "BaseCharacter.h"
#include "ContentsEnum.h"

class ARoom;
class USpriteRenderer;
class UEngineWinImage;
class AEnemyCharacter;

enum class EPlayerState
{
	Idle,
	Move,
	Attack,
	KnockBack,
	Interact,
};

/**
 *	플레이어 캐릭터 클래스
 */
class APlayerCharacter : public ABaseCharacter
{
public:
	/** 생성자, 소멸자 */
	APlayerCharacter();
	~APlayerCharacter() {}

	/** 객체 값 복사 */
	APlayerCharacter(const APlayerCharacter& _Other) = delete;
	APlayerCharacter(APlayerCharacter&& _Other) noexcept = delete;
	APlayerCharacter& operator=(const APlayerCharacter& _Other) = delete;
	APlayerCharacter& operator=(APlayerCharacter&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void StartInteract() override;
	virtual void Interact(float DeltaTime) override;

	virtual void LevelChangeStart() override;
	void LevelChangeEnd();

	void StartIdle();
	void StartMove();
	void StartAttack();
	void StartKnockBack();
	void Idle(float DeltaTime);
	void Move(float DeltaTime);
	void Attack(float DeltaTime);
	void KnockBack(float DeltaTime);
	void EndAttack();
	void ChangeState(EPlayerState ChangeState);
	virtual void TakeDamage(int Damage, ABaseCharacter* EnemyCharacter) override;
	void ChangePlayerDirection(FVector2D Dir);

	void RunSoundPlay();

	void PrintDebugInfo(float DeltaTime);
	void SetPlayerStateToIdle();

	void SetCameraLocationToPlayer();

	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);

	void PlayerCameraCheck();
	void PlayerGroundCheck(FVector2D MovePos);
	void Gravity(float _DeltaTime);

protected:

private:
	UCollision2D* HitCollision = nullptr;
	USoundPlayer EffectSoundPlayer;

	std::vector<UCollision2D*> AttackCollisions;
	UCollision2D* InteractCollision = nullptr;

	EPlayerState CurPlayerState = EPlayerState::Idle;
	EPlayerState PrevPlayerState = EPlayerState::Idle;

	FVector2D MoveDir = FVector2D::ZERO;
	FVector2D GravityForce = FVector2D::ZERO;
	FVector2D KnockBackDir = FVector2D::ZERO;

	int MySpriteIndex = 0;
	int IsGround = false;
	bool IsMove = false;
	bool IsAttack = false;
	float KnockBackTime = 0.0f;
};

