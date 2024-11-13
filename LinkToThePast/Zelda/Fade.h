#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

/**
 *	설명
 */
class AFade : public AActor
{
public:
	static AFade* Instance;

public:
	/** 생성자, 소멸자 */
	AFade();
	~AFade();

	/** 객체 값 복사 방지 */
	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

	void FadeIn();
	void FadeOut();

protected:

private:
	virtual void LevelChangeStart() override;
	void FadeChange();

	float FadeValue = 0.0f;
	float FadeDir = 1.0f;

	USpriteRenderer* BackSpriteRenderer = nullptr;

};

