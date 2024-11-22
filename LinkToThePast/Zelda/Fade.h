#pragma once
#include <EngineCore/Actor.h>

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

	void FadeIn();
	void FadeOut();

	void FadeInEnd();
	void FadeOutEnd();

	USpriteRenderer* GetBackSpriteRenderer()
	{
		return BackSpriteRenderer;
	}


protected:

private:
	virtual void LevelChangeStart() override;
	void FadeChange();

	float FadeValue = 0.0f;
	float FadeDir = 1.0f;

	bool IsFading = false;

	USpriteRenderer* BackSpriteRenderer = nullptr;

	std::function<void()> EndFunction = nullptr;

};

