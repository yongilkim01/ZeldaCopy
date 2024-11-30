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
 *	����
 */
class AFade : public AActor
{
public:
	/** ������, �Ҹ��� */
	AFade();
	~AFade();

	/** ��ü �� ���� ���� */
	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

	/** Fade Ŭ���� �޼ҵ� */
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
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

private:
	/** Fade Ŭ���� ������� �ʱ�ȭ */
	float FadeValue = 0.0f;
	float FadeDir = 1.0f;
	bool IsFading = false;
	bool bFadeOutOn = true;
	bool bFadeInOn = true;

	/** ������Ʈ */
	USpriteRenderer* AlphaRenderer = nullptr;
	USpriteRenderer* ZoomRenderer = nullptr;
};

