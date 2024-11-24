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
	SetEventActorRenderOrder();
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

void AEventActor::SetEventActorRenderOrder()
{
	if (nullptr != GetCurRoom())
	{
		int FloorOrder = 0;
		if (ERoomFloor::FLOOR_1F == GetCurRoom()->GetCuRoomFloor())
		{
			FloorOrder = static_cast<int>(ERenderOrder::FIRST_FLOOR_OBJ);
		}
		else
		{
			FloorOrder = static_cast<int>(ERenderOrder::SECOND_FLOOR_OBJ);
		}
		int Padding = GetActorLocation().iY() - GetCurRoom()->GetActorLocation().iY();
		this->SpriteRenderer->SetOrder(FloorOrder + Padding);
	}
}

void AEventActor::SetEventActorRenderOrder(int Order)
{
	SpriteRenderer->SetOrder(Order);
}

int AEventActor::GetEventActorRenderOrder()
{
	return SpriteRenderer->GetOrder();
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

FVector2D AEventActor::GetDirectionToTargetLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = TargetLocation - GetActorLocation();
	ResultDir.Normalize();

	// Up 또는 Down
	if (UEngineMath::Abs(ResultDir.Y) > UEngineMath::Abs(ResultDir.X))
	{
		if (ResultDir.Y > 0.0f)
		{
			return FVector2D::DOWN;
		}
		else
		{
			return FVector2D::UP;
		}
	}
	else // Right 또는 Left
	{
		if (ResultDir.X > 0.0f)
		{
			return FVector2D::RIGHT;
		}
		else
		{
			return FVector2D::LEFT;
		}
	}

	return FVector2D::ZERO;
}

FVector2D AEventActor::GetDirectionToThisLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = GetActorLocation() - TargetLocation;
	ResultDir.Normalize();

	// Up 또는 Down
	if (UEngineMath::Abs(ResultDir.Y) > UEngineMath::Abs(ResultDir.X))
	{
		if (ResultDir.Y > 0.0f)
		{
			return FVector2D::DOWN;
		}
		else
		{
			return FVector2D::UP;
		}
	}
	else // Right 또는 Left
	{
		if (ResultDir.X > 0.0f)
		{
			return FVector2D::RIGHT;
		}
		else
		{
			return FVector2D::LEFT;
		}
	}

	return FVector2D::ZERO;
}

FVector2D AEventActor::GetNormalDirectionToTargetLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = TargetLocation - GetActorLocation();
	ResultDir.Normalize();
	return ResultDir;
}

FVector2D AEventActor::GetNormalDirectionToThisLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = GetActorLocation() - TargetLocation;
	ResultDir.Normalize();
	return ResultDir;
}