#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayerCharacter;
class AUIMagicBar;
class AUIHeartManager;
/*
 *
 */
class AUIManager : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIManager();
	~AUIManager();

	/** 값 복사 방지 */
	AUIManager(const AUIManager& _Other) = delete;
	AUIManager(AUIManager&& _Other) noexcept = delete;
	AUIManager& operator=(const AUIManager& _Other) = delete;
	AUIManager& operator=(AUIManager&& _Other) noexcept = delete;

	void SetPlayer(APlayerCharacter* PlayerCharacter) { this->PlayerCharacter = PlayerCharacter; }
	APlayerCharacter* GetPlayer() { return this->PlayerCharacter; }

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	APlayerCharacter* PlayerCharacter = nullptr;

	AUIMagicBar* MagicBar = nullptr;
	AUIHeartManager* HeartManager = nullptr;
};

