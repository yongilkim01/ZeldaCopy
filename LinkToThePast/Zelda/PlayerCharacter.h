#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/Collision2D.h>

class ARoom;
class USpriteRenderer;
class UEngineWinImage;

enum class EPlayerState
{
	Idle,
	Move,
	Attack,
};

/**
 *	플레이어 캐릭터 클래스
 */
class APlayerCharacter : public AActor
{
public:
	/** 생성자, 소멸자 */
	APlayerCharacter();
	~APlayerCharacter();

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
	void Idle(float DeltaTime);
	void Move(float DeltaTime);
	void Attack(float DeltaTime);
	void ChangeState(EPlayerState ChangeState);

	void SetCollisionImage(std::string_view CollisionImageName);

	void RunSoundPlay();

	void PrintDebugPlayerState();
	void SetPlayerStateToIdle();

	void SetCameraLocationToPlayer();

	void SetCurRoom(ARoom* Room) { CurRoom = Room; }
	ARoom* GetCurRoom() { return CurRoom; }

	void PlayerCameraCheck();
	void PlayerGroundCheck(FVector2D MovePos);
	void Gravity(float _DeltaTime);

protected:

private:
	ARoom* CurRoom = nullptr;

	UEngineWinImage* CollisionImage = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* CollisionComponent = nullptr;

	EPlayerState CurState = EPlayerState::Idle;
	FVector2D CurDir = FVector2D::DOWN;
	FVector2D MoveDir = FVector2D::ZERO;
	FVector2D GravityForce = FVector2D::ZERO;

	float Speed = 250.0f;
	int MySpriteIndex = 0;
	int IsGround = false;
	bool IsMove = false;
};

