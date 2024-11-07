#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/Collision2D.h>

class ARoom;

enum class EPlayerState
{
	Idle,
	Move,
	Attack,
};

// Ό³Έν :
class APlayerCharacter : public AActor
{
public:
	// constrcuter destructer
	APlayerCharacter();
	~APlayerCharacter();

	// delete Function
	APlayerCharacter(const APlayerCharacter& _Other) = delete;
	APlayerCharacter(APlayerCharacter&& _Other) noexcept = delete;
	APlayerCharacter& operator=(const APlayerCharacter& _Other) = delete;
	APlayerCharacter& operator=(APlayerCharacter&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetCollisionImage(std::string_view CollisionImageName);

	void LevelChangeStart();
	void LevelChangeEnd();

	void RunSoundPlay();

	void PrintDebugPlayerState();
	void SetPlayerStateToIdle();

	void ChangeState(EPlayerState ChangeState);

	void IdleStart();
	void MoveStart();
	void AttackStart();

	void Idle(float DeltaTime);
	void Move(float DeltaTime);
	void Attack(float DeltaTime);

	void FollowCamera();

	void SetCurRoom(ARoom* Room) { CurRoom = Room; }
	ARoom* GetCurRoom() { return CurRoom; }

	void PlayerCameraCheck();
	void PlayerGroundCheck(FVector2D MovePos);
	void Gravity(float _DeltaTime);

	ARoom* CurRoom = nullptr;

	bool IsCameraControl = false;

protected:

private:
	float Speed = 100.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;

	EPlayerState CurState = EPlayerState::Idle;
	FVector2D CurDir = FVector2D::ZERO;
	FVector2D MoveDir = FVector2D::ZERO;
	class UEngineWinImage* CollisionImage = nullptr;

	UFSMStateManager FSM;

	int IsGround = false;
	bool IsMove = false;
	FVector2D GravityForce = FVector2D::ZERO;

	UCollision2D* Collision = nullptr;
};

