#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>

#include "ContentsEnum.h"

// Ό³Έν :
class ARoom : public AActor
{
public:
	// constrcuter destructer
	ARoom();
	~ARoom();

	// delete Function
	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

	void SetRoomSprite(std::string_view SpriteName, ERenderOrder RenderOrder, FVector2D SpritePos, float SpriteScale = 3.0f);

protected:

public:
	class USpriteRenderer* SpriteRenderer = nullptr;
};