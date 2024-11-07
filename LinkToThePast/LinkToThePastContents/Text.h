#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

class USpriteRenderer;
/**
 *	설명
 */
class AText : public AActor
{
public:
	/** 생성자, 소멸자 */
	AText();
	~AText();

	/** 객체 값 복사 방지 */
	AText(const AText& _Other) = delete;
	AText(AText&& _Other) noexcept = delete;
	AText& operator=(const AText& _Other) = delete;
	AText& operator=(AText&& _Other) noexcept = delete;

	void SetTextSpriteName(const std::string Text);
	void SetTextScale(FVector2D TextScale) { this->TextScale = TextScale; }

	template<typename EnumType>
	void SetOrder(EnumType Order) { SetOrder(static_cast<int>(Order)); }
	void SetOrder(int Order);
	void SetValue(int Score);

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	std::string TextSpriteName;
	FVector2D TextScale;
	std::vector<USpriteRenderer*> Renders;

};

