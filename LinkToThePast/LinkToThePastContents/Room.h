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

	FVector2D GetRoomSize() { return RoomSize; }
	void SetRoomSize(FVector2D Size) { RoomSize = Size; }
	void SetRoomSize(int SizeX, int SizeY) { RoomSize = { SizeX, SizeY }; }

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	class APlayer* PlayerCharacter = nullptr;
	FVector2D RoomSize = FVector2D::ZERO;
};