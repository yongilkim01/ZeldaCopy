#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include "Player.h"

ARoom::ARoom()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Dungeon1.png");
}

ARoom::~ARoom()
{
}

void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CheckPlayer(APlayer::StaticPlayer);
}

void ARoom::SetRoomSprite(std::string_view SpriteName, ERenderOrder RenderOrder, FVector2D SpritePos, float SpriteScale /* = 3.0f */)
{
	SpriteRenderer->SetOrder(RenderOrder);
	SpriteRenderer->SetSprite(SpriteName);

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(SpriteScale);
	SpriteRenderer->SetComponentLocation(MapScale.Half());
	SetActorLocation(SpritePos);
}

void ARoom::SetRoomSize(int SizeX, int SizeY)
{
	RoomSize = { SizeX, SizeY };
	LeftTopPos = GetActorLocation();
	RightBottomPos = GetActorLocation() + RoomSize;
	//SetActorScale(RoomSize);
}

bool ARoom::CheckPlayer(APlayer* PlayerCharacter)
{
	if (PlayerCharacter->GetActorLocation() > GetTransform().CenterLeftTop()
		&& PlayerCharacter->GetActorLocation() < GetTransform().CenterRightBottom())
	{
		/*PlayerCharacter->CurRoom->SetPlayer(nullptr);
		PlayerCharacter->CurRoom = this;*/

		return true;
	}
	
	return false;
}

void ARoom::SetPlayer(APlayer* PlayerCharacter)
{
	if (PlayerCharacter == nullptr) return;

	this->PlayerCharacter = PlayerCharacter;
}
