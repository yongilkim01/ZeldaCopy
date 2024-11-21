#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

/**
 *	����
 */
class AUIMagicBar : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIMagicBar();
	~AUIMagicBar();

	/** ��ü �� ���� ���� */
	AUIMagicBar(const AUIMagicBar& _Other) = delete;
	AUIMagicBar(AUIMagicBar&& _Other) noexcept = delete;
	AUIMagicBar& operator=(const AUIMagicBar& _Other) = delete;
	AUIMagicBar& operator=(AUIMagicBar&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* BackGroundRenderer = nullptr;
	USpriteRenderer* FrameRenderer = nullptr;
	USpriteRenderer* GageRenderer = nullptr;
};

