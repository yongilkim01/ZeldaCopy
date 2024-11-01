#pragma once
#include <EngineCore/Actor.h>

// ���� :
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

	class ARoom* CurRoom = nullptr;

protected:

private:
	float Speed = 100.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;
};

