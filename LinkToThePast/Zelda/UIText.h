#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

enum class ETextType
{
	NONE,
	HUD,
	STORY,
};

/**
 *	설명
 */
class AHUDText : public AActor
{
public:
	/** 생성자, 소멸자 */
	AHUDText();
	~AHUDText();

	/** 객체 값 복사 방지 */
	AHUDText(const AHUDText& _Other) = delete;
	AHUDText(AHUDText&& _Other) noexcept = delete;
	AHUDText& operator=(const AHUDText& _Other) = delete;
	AHUDText& operator=(AHUDText&& _Other) noexcept = delete;

	void InitText(FVector2D Size, int Count);
	void ShowText(float Time);
	void Reserve(int Count);
	int ConvertCharInteger(char c);
	void SetTextCount(int Count);
	void SetValue(int StrValue);

	std::string GetString() const
	{ 
		return StrValue; 
	}
	void SetTime(float Time)
	{ 
		this->Time = Time;
	}

protected:

private:
	std::vector<USpriteRenderer*> TextSprites;
	ETextType TextType = ETextType::NONE;
	FVector2D TextSize = FVector2D::ZERO;

	std::string StrValue;
	float Time = 0.0f;
	int TextCount = 0;

};

