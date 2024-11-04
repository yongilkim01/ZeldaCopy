#pragma once
#include <EngineCore/Actor.h>

enum class EPlayerState
{
	None = 0,
	Idle = 1,
	Move = 2,
	Attack = 3
};

// Ό³Έν :
class APlayer : public AActor
{
public:
	static APlayer* StaticPlayer;

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

	void LevelChangeStart();
	void LevelChangeEnd();

	void RunSoundPlay();

	void PrintDebugPlayerState();
	void SetPlayerStateToIdle();
	void PlayAttackAnimation(FVector2D Dir);

	void Idle();
	void Move();
	void Attack();

	void FollowCamera();

	class ARoom* CurRoom = nullptr;

protected:

private:
	float Speed = 100.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;

	EPlayerState CurState = EPlayerState::None;
	FVector2D CurDir = FVector2D::ZERO;
};

