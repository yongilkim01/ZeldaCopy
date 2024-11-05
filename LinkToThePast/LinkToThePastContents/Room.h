#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>

#include "ContentsEnum.h"

class USpriteRenderer;
class URoomMove;

// ���� :
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
	URoomMove* FindRoomMove(int Index) { return RoomMoves[Index]; }

	FVector2D GetRoomSize() { return RoomSize; }
	std::vector<ARoom*>& GetLinkedRoomes() { return LinkedRoomes; }
	void SetRoomSize(FVector2D Size) { SetRoomSize(Size.iX(), Size.iY()); }
	void SetRoomSize(int SizeX, int SizeY);
	void SetPlayer(class APlayer* PlayerCharacter);
	void AddRoomMove(URoomMove* RoomMove) { RoomMoves.push_back(RoomMove); }
	int GetRoomMovesSize() { return RoomMoves.size(); }

	FVector2D RoomSize = FVector2D::ZERO;
	FVector2D LeftTopPos = FVector2D::ZERO;
	FVector2D RightBottomPos = FVector2D::ZERO;

protected:

private:
	USpriteRenderer* BackSpriteRenderer;
	USpriteRenderer* ColSpriteRenderer;

	APlayer* PlayerCharacter = nullptr;

	std::vector<ARoom*> LinkedRoomes;

	std::vector<URoomMove*> RoomMoves;
};