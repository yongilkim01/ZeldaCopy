#include "PreCompile.h"
#include "UIBox.h"
#include "ContentsEnum.h"
#include "UIText.h"

#include <EngineCore/SpriteRenderer.h>

AUIBox::AUIBox()
{
	BoxRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BoxRenderer->SetSprite("UIBox.png");
	FVector2D BoxScale = BoxRenderer->SetSpriteScale(1.0f);
	BoxRenderer->SetComponentLocation(FVector2D::ZERO);
	BoxRenderer->SetComponentScale(BoxScale);
	BoxRenderer->SetOrder(ERenderOrder::UI);
	BoxRenderer->SetCameraEffect(false);
	BoxRenderer->SetAlphafloat(0.0f);
}

AUIBox::~AUIBox()
{
}

void AUIBox::BeginPlay()
{
	Super::BeginPlay();

}

void AUIBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUIBox::CreateUIText(std::string_view StrValue, float Time)
{
	AUIText* NewUIText = GetWorld()->SpawnActor<AUIText>();
	NewUIText->BeginPlayUIText(StrValue, Time);
	NewUIText->SetActive(false);
	UITextes.push_back(NewUIText);
}

void AUIBox::CreateUIText(const std::vector<std::string>& StrValues, float Time)
{
	AUIText* NewUIText = GetWorld()->SpawnActor<AUIText>();
	NewUIText->BeginPlayUIText(StrValues, Time);
	NewUIText->SetActive(false);
	UITextes.push_back(NewUIText);
}

void AUIBox::SetUIText(std::string_view StrValue, int Index, float Time)
{
	if (Index < UITextes.size()) 
	{
		UITextes[Index]->BeginPlayUIText(StrValue, Time);
	}
}

void AUIBox::SetUIText(const std::vector<std::string>& StrValues, int Index, float Time)
{
	if (Index < UITextes.size()) 
	{
		UITextes[Index]->BeginPlayUIText(StrValues, Time);
	}
}

void AUIBox::ShowUI(float DeltaTime)
{
	BoxRenderer->SetAlphafloat(1.0f);
	FVector2D Location = GetActorLocation() - FVector2D(330, 60);

	for (AUIText* UIText : UITextes)
	{
		Location.Y -= 30.0f;
		UIText->SetActive(true);
		UIText->ShowUIText(0.0f);
		UIText->SetActorLocation(Location);
	}
}

void AUIBox::HideUI()
{
	BoxRenderer->SetAlphafloat(0.0f);

	for (AUIText* UIText : UITextes)
	{
		UIText->SetActive(false);
	}
}

void AUIBox::SetTextsCount(int Count)
{
	for (int i = 0; i < Count; i++)
	{
		CreateUIText("");
	}
}
