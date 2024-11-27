#pragma once
#include <EngineCore/Actor.h>

class AHUDText;
class USpriteRenderer;

/**
 *	����
 */
class AUIArrowManager : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIArrowManager();
	~AUIArrowManager();

	/** ��ü �� ���� ���� */
	AUIArrowManager(const AUIArrowManager& _Other) = delete;
	AUIArrowManager(AUIArrowManager&& _Other) noexcept = delete;
	AUIArrowManager& operator=(const AUIArrowManager& _Other) = delete;
	AUIArrowManager& operator=(AUIArrowManager&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	AHUDText* UIText = nullptr;

};