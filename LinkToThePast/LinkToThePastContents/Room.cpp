#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include "ContentsEnum.h"
#include "Player.h"

ARoom::ARoom()
{
	{
		BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackSpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		BackSpriteRenderer->SetSprite("Dungeon1.png");
		FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
		BackSpriteRenderer->SetComponentLocation(MapScale.Half());
	}

	{
		ColSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ColSpriteRenderer->SetOrder(ERenderOrder::COLMAP);
		ColSpriteRenderer->SetSprite("Dungeon1Collision.png");
		FVector2D MapScale = ColSpriteRenderer->SetSpriteScale(1.0f);
		ColSpriteRenderer->SetComponentLocation(MapScale.Half());
	}
}

ARoom::~ARoom()
{
}

void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('Y'))
	{
		ColSpriteRenderer->SetActiveSwitch();
	}
}

void ARoom::SetRoomSprite(std::string_view SpriteName, ERenderOrder RenderOrder, FVector2D SpritePos, float SpriteScale /* = 3.0f */)
{
	BackSpriteRenderer->SetOrder(RenderOrder);
	BackSpriteRenderer->SetSprite(SpriteName);

	FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(SpriteScale);
	BackSpriteRenderer->SetComponentLocation(MapScale.Half());
	SetActorLocation(SpritePos);
}

void ARoom::LinkRoom(ARoom* LinkedRoom)
{
	this->LinkedRoomes.push_back(LinkedRoom);
	LinkedRoom->LinkedRoomes.push_back(this);
}

void ARoom::SetRoomSize(int SizeX, int SizeY)
{
	RoomSize = { SizeX, SizeY };
	LeftTopPos = GetActorLocation();
	RightBottomPos = GetActorLocation() + RoomSize;
	//SetActorScale(RoomSize);
}

void ARoom::SetPlayer(APlayer* PlayerCharacter)
{
	if (PlayerCharacter == nullptr) return;

	this->PlayerCharacter = PlayerCharacter;
}
