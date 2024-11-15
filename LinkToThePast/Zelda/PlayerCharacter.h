#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/Collision2D.h>
#include <EnginePlatform/EngineSound.h>

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
};

/**
 *	플레이어 캐릭터 클래스
 */
class APlayerCharacter : public AActor
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

	void LevelChangeStart();
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
	void TakeDamage(int Damage, AEnemyCharacter* EnemyCharacter);

	void SetCollisionImage(std::string_view CollisionImageName);

	void RunSoundPlay();

	void PrintDebugInfo(float DeltaTime);
	void SetPlayerStateToIdle();

	void SetCameraLocationToPlayer();

	void SetCurRoom(ARoom* Room);
	ARoom* GetCurRoom() { return CurRoom; }
	void SetRoomFloor(ERoomFloor RoomFloor)
	{
		this->CurRoomFloor = RoomFloor;
	}
	ERoomFloor GetRoomFloor()
	{
		return this->CurRoomFloor;
	}
	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);

	void PlayerCameraCheck();
	void PlayerGroundCheck(FVector2D MovePos);
	void Gravity(float _DeltaTime);

protected:

private:
	ARoom* CurRoom = nullptr;

	UEngineWinImage* CollisionImage = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* BodyCollisionComp = nullptr;
	UCollision2D* MoveCollisionComp = nullptr;
	USoundPlayer EffectSoundPlayer;

	std::vector<UCollision2D*> AttackCollisions;

	EPlayerState CurPlayerState = EPlayerState::Idle;
	EPlayerState PrevPlayerState = EPlayerState::Idle;

	ERoomFloor CurRoomFloor = ERoomFloor::FLOOR_1F;
	FVector2D CurDir = FVector2D::DOWN;
	FVector2D MoveDir = FVector2D::ZERO;
	FVector2D GravityForce = FVector2D::ZERO;
	FVector2D KnockBackDir = FVector2D::ZERO;

	float Speed = 250.0f;
	int MySpriteIndex = 0;
	int IsGround = false;
	bool IsMove = false;
	bool IsAttack = false;
	float KnockBackTime = 0.0f;

	int MaxHP = 100;
	int CurrentHP = 40;
};

