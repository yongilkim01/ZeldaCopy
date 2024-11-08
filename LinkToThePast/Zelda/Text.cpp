#include "PreCompile.h"
#include "Text.h"

AText::AText()
{
	// 일시적으로 10개 갯수 제한 지정
	for (size_t i = 0; i < 10; i++)
	{
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		Sprite->SetCameraEffect(false);
		Renders.push_back(Sprite);
	}
}

AText::~AText()
{
}

void AText::BeginPlay()
{
}

void AText::Tick(float DeltaTime)
{
}

void AText::SetTextSpriteName(const std::string Text)
{
	TextSpriteName = Text;
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}
}

void AText::SetOrder(int Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(Order);
	}
}

// int 정수형 값을 문자열로 바꾸는 코드
void AText::SetValue(int StrValue)
{
	std::string Number = std::to_string(StrValue);
	// 2000;
	// 0000002000
	if (Renders.size() <= Number.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}
	// 0000000000
	// 2000
	// 
	FVector2D Pos = FVector2D::ZERO;
	for (size_t i = 0; i < Number.size(); i++)
	{
		char Value = Number[i] - '0';
		Renders[i]->SetSprite(TextSpriteName, Value);
		Renders[i]->SetComponentScale(TextScale);
		Renders[i]->SetComponentLocation(Pos);
		Pos.X += TextScale.X;
		Renders[i]->SetActive(true);
	}
	for (size_t i = Number.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}
}