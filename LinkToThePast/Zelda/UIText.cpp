#include "PreCompile.h"
#include "UIText.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>

AHUDText::AHUDText()
{
}

AHUDText::~AHUDText()
{
}

void AHUDText::InitText(FVector2D Size, int Count)
{
	TextSprites.reserve(Count);

	// �Ͻ������� 10�� ���� ���� ����
	for (size_t i = 0; i < Count; i++)
	{
		USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
		Renderer->SetSprite("HUDText.png", 0);
		FVector2D TextScale = Renderer->SetSpriteScale(1.0f);
		Renderer->SetComponentScale(TextScale);
		Renderer->SetOrder(ERenderOrder::UI);
		Renderer->SetCameraEffect(false);
		Renderer->SetComponentLocation(FVector2D::ZERO + (Size * static_cast<float>(i)));
		TextSprites.push_back(Renderer);
	}

	float Padding = 0.0f;

	switch (Count)
	{
	case 1:
		Padding = 0.0f;
		break;
	case 2:
		Padding = 12.0f;
		break;
	case 3:
		Padding = 24.0f;
		break;
	default:
		break;
	}

	for (size_t i = 0; i < Count; i++)
	{
		TextSprites[i]->AddComponentLocation(FVector2D(-Padding, 0.0f));
	}

}

void AHUDText::ShowText(float Time)
{
}

void AHUDText::Reserve(int Count)
{
	// ��� �ؽ�Ʈ ��������Ʈ���� ��Ȱ��ȭ
	for (size_t i = 0; i < TextSprites.size(); i++)
	{
		TextSprites[i]->SetActive(false);
	}

	// ��������Ʈ ������ ũ�⸦ ���Ҵ�
	TextSprites.resize(Count);
}

int AHUDText::ConvertCharInteger(char c)
{
	return c - '0';
}

void AHUDText::SetTextCount(int Count)
{
	FVector2D StartLocation = FVector2D(-50.0f, 0.0f);
	// ��� �ؽ�Ʈ ��������Ʈ���� ��Ȱ��ȭ
	for (size_t i = 0; i < TextSprites.size(); i++)
	{
		StartLocation += FVector2D(25.0f, 0.0f);
		TextSprites[i]->SetComponentLocation(StartLocation);
	}
}

// int ������ ���� ���ڿ��� �ٲٴ� �ڵ�
void AHUDText::SetValue(int StrValue)
{
	std::string Number = std::to_string(StrValue);

	if (0 == Number.size())
	{
		MSGASSERT("���� ����� 0�Դϴ�.");
		return;
	}
	if (TextSprites.size() < Number.size())
	{
		MSGASSERT("�ڸ����� �Ѱ���ϴ�.");
		return;
	}

	for (size_t i = 0; i < TextSprites.size(); i++)
	{
		TextSprites[i]->SetSprite("HUDText.png", 0);
	}

	// 0000000000
	// 2000
	// 
	int TextSpriteLastIndex = static_cast<int>(TextSprites.size())- 1;
	for (int i = static_cast<int>(Number.size()) - 1; i >= 0; i--)
	{
		char Value = Number[i] - '0';
		TextSprites[TextSpriteLastIndex]->SetSprite("HUDText.png", Value);
		TextSpriteLastIndex--;
	}
}