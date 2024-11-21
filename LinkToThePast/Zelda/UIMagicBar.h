#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

/**
 *	설명
 */
class AUIMagicBar : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIMagicBar();
	~AUIMagicBar();

	/** 객체 값 복사 방지 */
	AUIMagicBar(const AUIMagicBar& _Other) = delete;
	AUIMagicBar(AUIMagicBar&& _Other) noexcept = delete;
	AUIMagicBar& operator=(const AUIMagicBar& _Other) = delete;
	AUIMagicBar& operator=(AUIMagicBar&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* BackGroundRenderer = nullptr;
	USpriteRenderer* FrameRenderer = nullptr;
	USpriteRenderer* GageRenderer = nullptr;
};

