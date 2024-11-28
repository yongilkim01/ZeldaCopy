#pragma once
#include "DropItem.h"
#include <EnginePlatform/EngineSound.h>

class AUIBox;

/**
 *	����
 */
class ADropLanternItem : public ADropItem
{
public:
	/** ������, �Ҹ��� */
	ADropLanternItem();
	~ADropLanternItem();

	/** ��ü �� ���� ���� */
	ADropLanternItem(const ADropLanternItem& _Other) = delete;
	ADropLanternItem(ADropLanternItem&& _Other) noexcept = delete;
	ADropLanternItem& operator=(const ADropLanternItem& _Other) = delete;
	ADropLanternItem& operator=(ADropLanternItem&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ADropItem ��� �޼ҵ� */
	virtual void StartDrop() override;
	virtual void StartPickup() override;
	virtual void Drop(float DeltaTime) override;
	virtual void Pickup(float DeltaTime) override;

protected:

private:
	float CheckTime = 3.5f;
	float CurrentTime = 0.0f;

	FVector2D CurDropPower = FVector2D::ZERO;
	USoundPlayer SoundPlayer;
	AUIBox* UIBox = nullptr;

};

