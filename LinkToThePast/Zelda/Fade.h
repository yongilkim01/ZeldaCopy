#pragma once
#include <EngineCore/Actor.h>

enum class EFadeType
{
	NONE,
	ALPHA,
	ZOOM,
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
	void ResetFade();

	USpriteRenderer* GetBackSpriteRenderer()
	{
		return AlphaRenderer;
	}
	bool IsFadeOutOn()
	{
		return bFadeOutOn;
	}
	void SetFadeOutOn(bool Value)
	{
		bFadeOutOn = Value;
	}
	bool IsFadeInOn()
	{
		return bFadeInOn;
	}
	void SetFadeInOn(bool Value)
	{
		bFadeInOn = Value;
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
	bool bFadeOutOn = true;
	bool bFadeInOn = true;

	/** 컴포넌트 */
	USpriteRenderer* AlphaRenderer = nullptr;
	USpriteRenderer* ZoomRenderer = nullptr;
};

