#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayerCharacter;
class AUIMagicBar;
class AUIHeartManager;
class AUIRupeeManager;
class AUIBombManager;
class AUIArrowManager;
class AUIKeyManager;

/*
 *
 */
class AUIManager : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIManager();
	~AUIManager();

	/** �� ���� ���� */
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
	AUIRupeeManager* RupeeManager = nullptr;
	AUIBombManager* BombManager = nullptr;
	AUIArrowManager* ArrowManager = nullptr;
	AUIKeyManager* KeyManager = nullptr;
};

