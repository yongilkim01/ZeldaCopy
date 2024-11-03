#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayer;
/*
 *
 */
class AUserInterface : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUserInterface();
	~AUserInterface();

	/** 값 복사 방지 */
	AUserInterface(const AUserInterface& _Other) = delete;
	AUserInterface(AUserInterface&& _Other) noexcept = delete;
	AUserInterface& operator=(const AUserInterface& _Other) = delete;
	AUserInterface& operator=(AUserInterface&& _Other) noexcept = delete;

	void SetPlayer(APlayer* PlayerCharacter) { this->PlayerCharacter = PlayerCharacter; }
	APlayer* GetPlayer() { return this->PlayerCharacter; }

	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	APlayer* PlayerCharacter = nullptr;
};

