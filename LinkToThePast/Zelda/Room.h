#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"

class USpriteRenderer;
class URoomMove;
class UEngineWinImage;
class ABaseCharacter;
class APlayerCharacter;

/**
 *	방 구조를 나타내는 클래스
 */
class ARoom : public AActor
{
public:
	/** 생성자, 소멸자 */
	ARoom();
	~ARoom();

	/** 값 객체 복사 방지 */
	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

	virtual void Tick(float DeltaTime) override;

	void PlayerLinkCheck();
	void SetPlayer(ABaseCharacter* PlayerCharacter);

	void SetRoomSprite(
		std::string_view SpriteName, 
		std::string_view CollisionName,
		ERenderOrder RenderOrder,
		FVector2D SpritePos, 
		float SpriteScale = 3.0f);

	void LinkRoom(ARoom* LinkedRoom);

	FVector2D GetRoomSize() { return RoomSize; }
	void SetRoomSize(FVector2D Size) { SetRoomSize(Size.iX(), Size.iY()); }
	void SetRoomSize(int SizeX, int SizeY);

	USpriteRenderer* GetColSpriteRenderer2F()
	{
		return this->ColSpriteRenderer2F;
	}
	UEngineWinImage* GetColWinImage1F();
	UEngineWinImage* GetColWinImage2F();
	UEngineWinImage* GetCurColWinImage()
	{
		return this->CurrentCollisionWinImage;
	}
	void SetCulWinImageTo1F();
	void SetCulWinImageTo2F();
	
	bool GetIsSecondFloor() { return this->IsSecondFloor; }
	void SetIsSecondFloor(bool IsSecondFloor) { this->IsSecondFloor = IsSecondFloor; }
	
	ERoomFloor GetCuRoomFloor()
	{
		return this->CurFloor;
	}

	void AddEnvSprite(USpriteRenderer* SpriteRender)
	{
		EnvSprites.push_back(SpriteRender);
	}

	void CreateEnvSprite(std::string_view SpriteName, FVector2D Location, FVector2D Size);

	FVector2D RoomSize = FVector2D::ZERO;
	FVector2D LeftTopPos = FVector2D::ZERO;
	FVector2D RightBottomPos = FVector2D::ZERO;

protected:

private:
	USpriteRenderer* BackSpriteRenderer = nullptr;
	USpriteRenderer* ColSpriteRenderer1F = nullptr;
	USpriteRenderer* ColSpriteRenderer2F = nullptr;

	USpriteRenderer* CurColSpriteRenderer = nullptr;

	UEngineWinImage* CurrentCollisionWinImage = nullptr;

	APlayerCharacter* PlayerCharacter = nullptr;

	ERoomFloor CurFloor = ERoomFloor::FLOOR_1F;

	std::vector<USpriteRenderer*> EnvSprites;

	bool IsSecondFloor = false;
	bool IsDebugRenderMode = false;
};