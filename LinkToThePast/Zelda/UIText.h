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
class AUIText : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIText();
	~AUIText();

	/** 객체 값 복사 방지 */
	AUIText(const AUIText& _Other) = delete;
	AUIText(AUIText&& _Other) noexcept = delete;
	AUIText& operator=(const AUIText& _Other) = delete;
	AUIText& operator=(AUIText&& _Other) noexcept = delete;

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

