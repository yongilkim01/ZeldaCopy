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

	USpriteRenderer* GetBackSpriteRenderer()
	{
		return AlphaRenderer;
	}

	/** ��, �� �޼ҵ� */
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
	bool bFadeOn = true;

	/** ������Ʈ */
	USpriteRenderer* AlphaRenderer = nullptr;
	USpriteRenderer* ZoomRenderer = nullptr;

	EFadeSize FadeSize = EFadeSize::NORMAL;
};

