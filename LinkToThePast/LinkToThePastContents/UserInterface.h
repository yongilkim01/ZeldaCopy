#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayerCharacter;
/*
 *
 */
class AUserInterface : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUserInterface();
	~AUserInterface();

	/** �� ���� ���� */
	AUserInterface(const AUserInterface& _Other) = delete;
	AUserInterface(AUserInterface&& _Other) noexcept = delete;
	AUserInterface& operator=(const AUserInterface& _Other) = delete;
	AUserInterface& operator=(AUserInterface&& _Other) noexcept = delete;

	void SetPlayer(APlayerCharacter* PlayerCharacter) { this->PlayerCharacter = PlayerCharacter; }
	APlayerCharacter* GetPlayer() { return this->PlayerCharacter; }

	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	APlayerCharacter* PlayerCharacter = nullptr;
};

