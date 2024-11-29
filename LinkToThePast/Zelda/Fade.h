#pragma once
#include <EngineCore/Actor.h>

enum class EFadeType
{
	NONE,
	ALPHA,
	ZOOM,
};

enum class EFadeSize
{
	NORMAL,
	BIG,
};

class USpriteRenderer;

/**
 *	설명
 */
class AFade : public AActor
{
public:
	/** 생성자, 소멸자 */
	AFade();
	~AFade();

	/** 객체 값 복사 방지 */
	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

	/** Fade 클래스 메소드 */
	void FadeIn();
	void FadeOut();

	void FadeChange();

	USpriteRenderer* GetBackSpriteRenderer()
	{
		return AlphaRenderer;
	}

	/** 겟, 셋 메소드 */
	EFadeSize GetFadeSize()
	{
		return FadeSize;
	}
	void SetFadeSize(EFadeSize FadeSize)
	{
		this->FadeSize = FadeSize;
	}
	bool IsFadeOn()
	{
		return bFadeOn;
	}
	void SetFadeOn(bool Value)
	{
		bFadeOn = Value;
	}

protected:
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

private:
	/** Fade 클래스 멤버변수 초기화 */
	float FadeValue = 0.0f;
	float FadeDir = 1.0f;
	bool IsFading = false;
	bool bFadeOn = true;

	/** 컴포넌트 */
	USpriteRenderer* AlphaRenderer = nullptr;
	USpriteRenderer* ZoomRenderer = nullptr;

	EFadeSize FadeSize = EFadeSize::NORMAL;
};

