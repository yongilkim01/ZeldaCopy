#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UCollision2D;
class AFade;
class APlayerCharacter;

/**
 *	설명
 */
class ALevelMove : public AActor
{
public:
	/** 생성자, 소멸자 */
	ALevelMove();
	~ALevelMove();

	/** 객체 값 복사 방지 */
	ALevelMove(const ALevelMove& _Other) = delete;
	ALevelMove(ALevelMove&& _Other) noexcept = delete;
	ALevelMove& operator=(const ALevelMove& _Other) = delete;
	ALevelMove& operator=(ALevelMove&& _Other) noexcept = delete;

	/** 겟, 셋 메소드 */
	void SetFade(AFade* FadeActor)
	{
		this->FadeIn = FadeActor;
	}
	void SetMoveLevelName(std::string_view LevelName)
	{
		MoveLevel = LevelName;
	}
	bool IsFadeOut()
	{
		return bFadeOut;
	}
	void SetIsFadeOut(bool Fade)
	{
		bFadeOut = Fade;
	}
	bool IsFadeIn()
	{
		return bFadeIn;
	}
	void SetIsFadeIn(bool Fade)
	{
		bFadeIn = Fade;
	}

protected:
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool bFadeOut = true;
	bool bFadeIn = true;

	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* Collision = nullptr;
	AFade* FadeIn = nullptr;
	APlayerCharacter* Player = nullptr;
	
	std::string MoveLevel;
};

