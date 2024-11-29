#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UCollision2D;
class AFade;
class APlayerCharacter;

/**
 *	����
 */
class ALevelMove : public AActor
{
public:
	/** ������, �Ҹ��� */
	ALevelMove();
	~ALevelMove();

	/** ��ü �� ���� ���� */
	ALevelMove(const ALevelMove& _Other) = delete;
	ALevelMove(ALevelMove&& _Other) noexcept = delete;
	ALevelMove& operator=(const ALevelMove& _Other) = delete;
	ALevelMove& operator=(ALevelMove&& _Other) noexcept = delete;

	/** ��, �� �޼ҵ� */
	void SetFade(AFade* FadeActor)
	{
		this->FadeActor = FadeActor;
	}
	void SetMoveLevelName(std::string_view LevelName)
	{
		MoveLevel = LevelName;
	}
	bool GetFade()
	{
		return IsFade;
	}
	void SetFade(bool Fade)
	{
		IsFade = Fade;
	}

protected:
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool IsFade = true;

	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* Collision = nullptr;
	AFade* FadeActor = nullptr;
	APlayerCharacter* Player = nullptr;
	
	std::string MoveLevel;
};

