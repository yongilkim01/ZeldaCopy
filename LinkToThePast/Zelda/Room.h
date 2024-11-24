#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
#include "Door.h"

enum class ERoomState
{
	NORMAL,
	GIMMICK,
};

enum class ERoomType
{
	NORMAL,
	GIMMICK,
};

enum class EGimmickType
{
	NONE,
	ENEMY,
};

class USpriteRenderer;
class URoomMove;
class UEngineWinImage;
class ABaseCharacter;
class APlayerCharacter;
class UCollision2D;



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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void StartGimmick();
	void StartNormal();

	void Gimmick(float DeltaTime);
	void Normal(float DeltaTime);

	void ChangeState(ERoomState State);

	void PrintDebugRoomInfo();
	void AddDoor(FVector2D Location, ERoomFloor RoomFloor, EDoorType Type, EDoorState State, EDoorDirection Direction);
	void SetGimmickCollision(FVector2D Location, FVector2D Size);

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

	void CreateEnvSprite(std::string_view SpriteName, FVector2D Location, FVector2D Size, ERenderOrder Floor);

	void SetOnlySecondFloor(bool IsOnlySecondFloor)
	{
		this->IsOnlySecondFloor = IsOnlySecondFloor;
	}

	bool GetOnlySecondFloor()
	{
		return this->IsOnlySecondFloor;
	}
	void SetRoomType(ERoomType RoomType)
	{
		this->RoomType = RoomType;
	}
	ERoomType GetRoomType()
	{
		return RoomType;
	}
	void AddEnemyCount(int Count)
	{
		EnemyCount += Count;
	}
	int GetEnemyCount()
	{
		return EnemyCount;
	}

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

	UCollision2D* GimmickCollision = nullptr;

	APlayerCharacter* PlayerCharacter = nullptr;

	ERoomFloor CurFloor = ERoomFloor::FLOOR_1F;
	ERoomState CurRoomState = ERoomState::NORMAL;
	ERoomType RoomType = ERoomType::NORMAL;

	std::vector<USpriteRenderer*> EnvSprites;
	std::vector<ADoor*> Doores;

	bool IsSecondFloor = false;
	bool IsDebugRenderMode = false;
	bool IsOnlySecondFloor = false;

	int EnemyCount = 0;
};