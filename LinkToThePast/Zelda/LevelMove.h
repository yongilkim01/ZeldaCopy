#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UCollision2D;

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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* Collision = nullptr;

};
