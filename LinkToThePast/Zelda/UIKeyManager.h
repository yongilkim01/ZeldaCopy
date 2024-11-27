#pragma once
#include <EngineCore/Actor.h>

class AHUDText;
class USpriteRenderer;

/**
 *	����
 */
class AUIKeyManager : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIKeyManager();
	~AUIKeyManager();

	/** ��ü �� ���� ���� */
	AUIKeyManager(const AUIKeyManager& _Other) = delete;
	AUIKeyManager(AUIKeyManager&& _Other) noexcept = delete;
	AUIKeyManager& operator=(const AUIKeyManager& _Other) = delete;
	AUIKeyManager& operator=(AUIKeyManager&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	AHUDText* UIText = nullptr;

};