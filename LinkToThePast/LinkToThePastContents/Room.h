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

	virtual void Tick(float DeltaTime) override;

	void SetRoomSprite(std::string_view SpriteName, ERenderOrder RenderOrder, FVector2D SpritePos, float SpriteScale = 3.0f);
	void LinkRoom(ARoom* LinkedRoom);

	FVector2D GetRoomSize() { return RoomSize; }
	std::vector<ARoom*>& GetLinkedRoomes() { return LinkedRoomes; }
	void SetRoomSize(FVector2D Size) { SetRoomSize(Size.iX(), Size.iY()); }
	void SetRoomSize(int SizeX, int SizeY);

	void SetPlayer(class APlayer* PlayerCharacter);

	FVector2D RoomSize = FVector2D::ZERO;
	FVector2D LeftTopPos = FVector2D::ZERO;
	FVector2D RightBottomPos = FVector2D::ZERO;

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	class APlayer* PlayerCharacter = nullptr;

	std::vector<ARoom*> LinkedRoomes;
};