#pragma once
#include <EngineCore/Actor.h>

class AHUDText;
class USpriteRenderer;

/**
 *	����
 */
class AUIRupeeManager : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIRupeeManager();
	~AUIRupeeManager();

	/** ��ü �� ���� ���� */
	AUIRupeeManager(const AUIRupeeManager& _Other) = delete;
	AUIRupeeManager(AUIRupeeManager&& _Other) noexcept = delete;
	AUIRupeeManager& operator=(const AUIRupeeManager& _Other) = delete;
	AUIRupeeManager& operator=(AUIRupeeManager&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	AHUDText* UIText = nullptr;

};