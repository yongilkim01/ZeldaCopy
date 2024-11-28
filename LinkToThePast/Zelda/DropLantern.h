#pragma once
#include "DropItem.h"
#include <EnginePlatform/EngineSound.h>

class AUIBox;

/**
 *	설명
 */
class ADropLanternItem : public ADropItem
{
public:
	/** 생성자, 소멸자 */
	ADropLanternItem();
	~ADropLanternItem();

	/** 객체 값 복사 방지 */
	ADropLanternItem(const ADropLanternItem& _Other) = delete;
	ADropLanternItem(ADropLanternItem&& _Other) noexcept = delete;
	ADropLanternItem& operator=(const ADropLanternItem& _Other) = delete;
	ADropLanternItem& operator=(ADropLanternItem&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ADropItem 상속 메소드 */
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

