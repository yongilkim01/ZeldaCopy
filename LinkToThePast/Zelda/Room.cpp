#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "BaseCharacter.h"
#include "RoomMove.h"
#include "Door.h"

ARoom::ARoom()
{
	{
		BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackSpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		BackSpriteRenderer->SetSprite("CastleDungeon1.png");
		FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
		BackSpriteRenderer->SetComponentLocation(MapScale.Half());
	}

	{
		ColSpriteRenderer1F = CreateDefaultSubObject<USpriteRenderer>();
		ColSpriteRenderer1F->SetOrder(ERenderOrder::COLMAP);
		ColSpriteRenderer1F->SetSprite("CastleDungeon1Collision.png");
		FVector2D MapScale = ColSpriteRenderer1F->SetSpriteScale(1.0f);
		ColSpriteRenderer1F->SetComponentLocation(MapScale.Half());
		ColSpriteRenderer1F->SetActive(false);
	}

	{
		ColSpriteRenderer2F = CreateDefaultSubObject<USpriteRenderer>();
		ColSpriteRenderer2F->SetOrder(ERenderOrder::COLMAP);
		ColSpriteRenderer2F->SetSprite("CastleDungeon1Collision2F.png");
		FVector2D MapScale = ColSpriteRenderer2F->SetSpriteScale(1.0f);
		ColSpriteRenderer2F->SetComponentLocation(MapScale.Half());
		ColSpriteRenderer2F->SetActive(false);
	}

	CurColSpriteRenderer = ColSpriteRenderer1F;
	CurrentCollisionWinImage = UImageManager::GetInst().FindImage(ColSpriteRenderer1F->GetCurSpriteName());

	EnvSprites.reserve(10);
	Doores.reserve(5);
}

ARoom::~ARoom()
{
}

void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('Y'))
	{
		this->IsDebugRenderMode = !this->IsDebugRenderMode;
	}	

	if (CurColSpriteRenderer != nullptr)
	{
		CurColSpriteRenderer->SetActive(IsDebugRenderMode);
	}
}

void ARoom::AddDoor(FVector2D Location, ERoomFloor RoomFloor, EDoorType Type, EDoorState State, EDoorDirection Direction)
{
	ADoor* Door = GetWorld()->SpawnActor<ADoor>();
	Door->SetActorLocation(GetActorLocation() + Location);
	Door->SetDoorDirection(Direction);
	Door->SetDoorType(Type);

	int RenderOrder = 0;

	switch (RoomFloor)
	{
	case ERoomFloor::FLOOR_1F:
		RenderOrder = static_cast<int>(ERenderOrder::FIRST_FLOOR) + 1;
		Door->SetDoorRenderOrder(RenderOrder);
		break;
	case ERoomFloor::FLOOR_2F:
		RenderOrder = static_cast<int>(ERenderOrder::SECOND_FLOOR) + 2;
		Door->SetDoorRenderOrder(RenderOrder);
		break;
	default:
		break;
	}

	Door->ChangeState(State);

}

void ARoom::SetRoomSprite(std::string_view SpriteName, std::string_view CollisionSpriteName, ERenderOrder RenderOrder, FVector2D SpritePos, float SpriteScale /* = 3.0f */)
{
	BackSpriteRenderer->SetOrder(RenderOrder);
	BackSpriteRenderer->SetSprite(SpriteName);
	FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(SpriteScale);
	BackSpriteRenderer->SetComponentLocation(MapScale.Half());

	ColSpriteRenderer1F->SetOrder(ERenderOrder::COLMAP);
	ColSpriteRenderer1F->SetSprite(CollisionSpriteName);
	FVector2D ColMapScale = ColSpriteRenderer1F->SetSpriteScale(SpriteScale);
	ColSpriteRenderer1F->SetComponentLocation(ColMapScale.Half());

	SetActorLocation(SpritePos);
	//ColSpriteRenderer->SetActorL
}


void ARoom::SetRoomSize(int SizeX, int SizeY)
{
	RoomSize = { SizeX, SizeY };
	LeftTopPos = GetActorLocation();
	RightBottomPos = GetActorLocation() + RoomSize;
	//SetActorScale(RoomSize);
}

UEngineWinImage* ARoom::GetColWinImage1F()
{
	return UImageManager::GetInst().FindImage(this->ColSpriteRenderer1F->GetCurSpriteName());
}

UEngineWinImage* ARoom::GetColWinImage2F()
{
	return UImageManager::GetInst().FindImage(this->ColSpriteRenderer2F->GetCurSpriteName());
}

void ARoom::SetCulWinImageTo1F()
{
	this->CurrentCollisionWinImage = UImageManager::GetInst().FindImage(this->ColSpriteRenderer1F->GetCurSpriteName());
	this->CurFloor = ERoomFloor::FLOOR_1F;
	CurColSpriteRenderer->SetActive(false);
	CurColSpriteRenderer = ColSpriteRenderer1F;
}

void ARoom::SetCulWinImageTo2F()
{
	this->CurrentCollisionWinImage = UImageManager::GetInst().FindImage(this->ColSpriteRenderer2F->GetCurSpriteName());
	this->CurFloor = ERoomFloor::FLOOR_2F;
	CurColSpriteRenderer->SetActive(false);
	CurColSpriteRenderer = ColSpriteRenderer2F;
}

void ARoom::CreateEnvSprite(std::string_view SpriteName, FVector2D Location, FVector2D Size, ERenderOrder Floor)
{
	USpriteRenderer* EnvSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

	int SecondFloorOrder = 0;

	if (Floor == ERenderOrder::SECOND_FLOOR)
	{
		SecondFloorOrder = static_cast<int>(Floor);
	}
	else
	{
		SecondFloorOrder = static_cast<int>(Floor) + 3000;
	}
	EnvSpriteRenderer->SetOrder(SecondFloorOrder);
	EnvSpriteRenderer->SetSprite(SpriteName);
	FVector2D EnvScale = EnvSpriteRenderer->SetSpriteScale(1.0f);
	EnvSpriteRenderer->SetComponentLocation(EnvScale.Half());
	EnvSpriteRenderer->SetComponentLocation(Location + Size.Half());
}

void ARoom::SetPlayer(ABaseCharacter* PlayerCharacter)
{
	if (PlayerCharacter == nullptr) return;

	this->PlayerCharacter = dynamic_cast<APlayerCharacter*>(PlayerCharacter);
}

void ARoom::PlayerLinkCheck()
{
	// TODO: 
	std::string SpriteName = ColSpriteRenderer1F->GetCurSpriteName();
	UEngineWinImage* WinImage = UImageManager::GetInst().FindImage(SpriteName);
}
