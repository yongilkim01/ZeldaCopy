#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>

class ARoom;

enum class EPlayerState
{
	Idle,
	Move,
	Attack,
};

// Ό³Έν :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

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

	ARoom* CurRoom = nullptr;

	bool IsCameraControl = false;

protected:

private:
	float Speed = 100.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;

	EPlayerState CurState = EPlayerState::Idle;
	FVector2D CurDir = FVector2D::ZERO;
	class UEngineWinImage* CollisionImage = nullptr;

	UFSMStateManager FSM;
};

