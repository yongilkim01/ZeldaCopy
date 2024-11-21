#pragma once
#include <EngineCore/Actor.h>

class AUIText;
class USpriteRenderer;

/**
 *	����
 */
class AUIBombManager : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIBombManager();
	~AUIBombManager();

	/** ��ü �� ���� ���� */
	AUIBombManager(const AUIBombManager& _Other) = delete;
	AUIBombManager(AUIBombManager&& _Other) noexcept = delete;
	AUIBombManager& operator=(const AUIBombManager& _Other) = delete;
	AUIBombManager& operator=(AUIBombManager&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	AUIText* UIText = nullptr;

};