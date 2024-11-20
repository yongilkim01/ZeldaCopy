#include "PreCompile.h"
#include "EventActor.h"

#include "Room.h"

AEventActor::AEventActor()
{

}

AEventActor::~AEventActor()
{
}

void AEventActor::BeginPlay()
{
	Super::BeginPlay();
}

void AEventActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEventActor::HoldToCharacter(FVector2D CharacterDirction)
{
	if (CharacterDirction == FVector2D::RIGHT)
	{

	}
	else if (CharacterDirction == FVector2D::LEFT)
	{

	}
	else if (CharacterDirction == FVector2D::UP)
	{

	}
	else if (CharacterDirction == FVector2D::DOWN)
	{

	}
}

void AEventActor::AddEventActorLocation(FVector2D Location)
{
	FVector2D CheckLocation = GetActorLocation() + Location;
	CheckLocation -= GetCurRoom()->GetActorLocation();

	if (CollisionImage != nullptr)
	{
		UColor CenterColor = CollisionImage->GetColor(CheckLocation, UColor::PINK);

		if (CenterColor != UColor::PINK)
		{
			AddActorLocation(Location);
		}
		else if (CenterColor == UColor::PINK)
		{
			DestoryEventActor();
		}
	}
}

void AEventActor::SetCurRoom(ARoom* Room, ERoomFloor RoomFloor)
{
	CurRoom = Room;

	switch (RoomFloor)
	{
	case ERoomFloor::FLOOR_1F:
		CollisionImage = CurRoom->GetColWinImage1F();
		break;
	case ERoomFloor::FLOOR_2F:
		CollisionImage = CurRoom->GetColWinImage2F();
		break;
	default:
		break;
	}
}

