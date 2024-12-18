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
class AEventActor;
class ALantern;
class AWeaponItem;
class ABow;
class ALantern;

enum class EPlayerState
{
	Idle,
	Move,
	Attack,
	Skill,
	KnockBack,
	Interact,
	Lift,
	LiftIdle,
	LiftMove,
	Sleep,
	WakeUp,
	Fall,
	TurnFall,
	SwordGet,
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
	virtual void TakeDamage(int Damage, AActor* EnemyCharacter) override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

	void CreateItem();

	void StartIdle();
	void Idle(float DeltaTime);

	void StartMove();
	void Move(float DeltaTime);

	void StartAttack();
	void Attack(float DeltaTime);

	void StartSkill();
	void Skill(float DeltaTime);

	void StartKnockBack();
	void KnockBack(float DeltaTime);

	void StartLift();
	void Lift(float DeltaTime);

	void StartLiftIdle();
	void LiftIdle(float DeltaTime);

	void StartLiftMove();
	void LiftMove(float DeltaTime);

	void StartSleep();
	void StartWakeUp();
	void StartFall();
	void StartTurnFall();
	void StartSwordGet();
	
	
	void Sleep(float DeltaTime);
	void WakeUp(float DeltaTime);
	void Fall(float DeltaTime);
	void TurnFall(float DeltaTime);
	void GetSword(float DeltaTime);

	void EndAttack();
	void EndLift();

	void ChangeState(EPlayerState ChangeState);
	void ChangePlayerDirection(FVector2D Dir);
	void CheckInteract();

	void RunSoundPlay();

	void SetPlayerStateToIdle();
	void SetCameraLocationToPlayer();

	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);

	void PlayerCameraCheck();
	void PlayerGroundCheck(FVector2D MovePos);
	void Gravity(float _DeltaTime);

	void PrintDebugInfo(float DeltaTime);

	ALantern* GetLantern()
	{
		return Lantern;
	}
	std::string GetWeaponUISpriteByIndex(int Index);

	float GetChildDistance()
	{
		return ChildDistance;
	}
	ABow* GetBow()
	{
		return Bow;
	}

protected:

private:
	std::vector<AWeaponItem*> WeaponItemes;

	ALantern* Lantern = nullptr;

	USoundPlayer EffectSoundPlayer;

	UCollision2D* HitCollision = nullptr;
	UCollision2D* AttackCollision = nullptr;
	UCollision2D* InteractCollision = nullptr;

	EPlayerState CurPlayerState = EPlayerState::Idle;
	EPlayerState PrevPlayerState = EPlayerState::Idle;

	FVector2D MoveDir = FVector2D::ZERO;
	FVector2D GravityForce = FVector2D::ZERO;
	FVector2D KnockBackDir = FVector2D::ZERO;

	AEventActor* OwnedEventActor = nullptr;

	ABow* Bow = nullptr;

	int MySpriteIndex = 0;
	int IsGround = false;
	bool IsMove = false;
	bool IsAttack = false;
	float KnockBackTime = 0.0f;
	float ChildDistance = 25.0f;
};

