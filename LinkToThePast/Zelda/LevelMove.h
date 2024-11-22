#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UCollision2D;
class AFade;

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

	void SetFade(AFade* FadeActor)
	{
		this->FadeActor = FadeActor;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* Collision = nullptr;
	AFade* FadeActor = nullptr;

};

