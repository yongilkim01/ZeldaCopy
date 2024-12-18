#include "PreCompile.h"
#include "BaseCharacter.h"
#include "Room.h"
#include "EventActor.h"
#include "EventManager.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>

ABaseCharacter::ABaseCharacter()
{

}

ABaseCharacter::~ABaseCharacter()
{

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == UEventManager::GetInstance().GetEventPause()) return;

	if (SpriteRenderer != nullptr)
	{
		SetCharacterRenderOrder();
	}
}


void ABaseCharacter::AddCharacterLocation(FVector2D MoveDirection)
{
	FVector2D CheckLocation = GetActorLocation() + MoveDirection;
	CheckLocation -= GetCurRoom()->GetActorLocation();

	if (CollisionImage != nullptr)
	{
		AEventActor* Result = nullptr;
			
		if (BodyCollision != nullptr)
		{
			FVector2D PrevCollisionLocation = MoveDirection;
			PrevCollisionLocation.Normalize();
			BodyCollision->AddComponentLocation(PrevCollisionLocation);
			Result = dynamic_cast<AEventActor*>(BodyCollision->CollisionOnce(ECollisionGroup::NOTMOVEABLE));
		}

		if (Result == nullptr)
		{

			UColor CenterColor = CollisionImage->GetColor(CheckLocation, UColor::PINK);
			UColor LeftTopColor = CollisionImage->GetColor(CheckLocation + FVector2D{ -CollisionSize.X, 0.0f }, UColor::PINK);
			UColor LeftBottomColor = CollisionImage->GetColor(CheckLocation + FVector2D{ -CollisionSize.X, CollisionSize.Y }, UColor::PINK);
			UColor RightTopColor = CollisionImage->GetColor(CheckLocation + FVector2D{ CollisionSize.X, 0.0f }, UColor::PINK);
			UColor RightBottomColor = CollisionImage->GetColor(CheckLocation + FVector2D{ CollisionSize.X, CollisionSize.Y }, UColor::PINK);

			if (CurRoom->GetIsSecondFloor() &&
				CenterColor == UColor::ROOM_UPSTAIRS)
			{
				CurRoom->SetCulWinImageTo2F();
				this->CurRoomFloor = ERoomFloor::FLOOR_2F;
				this->CollisionImage = CurRoom->GetColWinImage2F();
				MoveDirection *= 0.75f;
				//FootSoundPlayer = UEngineSound::Play("stairs up 1.wav");
			}
			else if (CurRoom->GetIsSecondFloor() &&
				(CenterColor == UColor::ROOM_DOWNSTAIRS ||
					LeftTopColor == UColor::ROOM_DOWNSTAIRS ||
					LeftBottomColor == UColor::ROOM_DOWNSTAIRS ||
					RightTopColor == UColor::ROOM_DOWNSTAIRS ||
					RightBottomColor == UColor::ROOM_DOWNSTAIRS))
			{
				CurRoom->SetCulWinImageTo1F();
				this->CurRoomFloor = ERoomFloor::FLOOR_1F;
				this->CollisionImage = CurRoom->GetColWinImage1F();
				MoveDirection *= 0.75f;
			}

			if (CenterColor != UColor::PINK &&
				LeftTopColor != UColor::PINK &&
				LeftBottomColor != UColor::PINK &&
				RightTopColor != UColor::PINK &&
				RightBottomColor != UColor::PINK)
			{
				AddActorLocation(MoveDirection);
			}
		}
	}
	BodyCollision->SetComponentLocation(FVector2D(0, 10));
}

void ABaseCharacter::SetCurRoom(ARoom* Room, bool IsPlayer)
{
	if (this->CurRoom != nullptr)
	{
		this->CurRoom->SetPlayer(nullptr);
		this->CurRoom = nullptr;
		this->CollisionImage = nullptr;
	}

	this->CurRoom = Room;

	if(true == IsPlayer)
	{
		this->CurRoom->SetPlayer(this);
	}
	else
	{
		this->CurRoom->AddEnemyCount(1);
	}

	if (CurRoom->GetOnlySecondFloor())
	{
		this->CurRoomFloor = ERoomFloor::FLOOR_2F;
		SetCollisionImage(CurRoom->GetColWinImage1F()->GetName());
		CurRoom->SetCulWinImageTo1F();
		SpriteRenderer->SetOrder(ERenderOrder::SECOND_FLOOR_OBJ);
	}
	else
	{
		if (CurRoom->GetIsSecondFloor())
		{

			if (CurRoom->GetStartSecondFloor())
			{
				CurRoomFloor = ERoomFloor::FLOOR_2F;
				SetCollisionImage(CurRoom->GetColWinImage2F()->GetName());
				CurRoom->SetCulWinImageTo2F();
			}
			else
			{
				switch (CurRoomFloor)
				{
				case ERoomFloor::FLOOR_1F:
					SetCollisionImage(CurRoom->GetColWinImage1F()->GetName());
					CurRoom->SetCulWinImageTo1F();
					break;
				case ERoomFloor::FLOOR_2F:
					SetCollisionImage(CurRoom->GetColWinImage2F()->GetName());
					CurRoom->SetCulWinImageTo2F();
					break;
				default:
					break;
				}
			}
		}
		else
		{
			SetCollisionImage(CurRoom->GetColWinImage1F()->GetName());
		}
	}
}

void ABaseCharacter::SetCollisionImage(std::string_view CollisionImageName)
{
	CollisionImage = UImageManager::GetInst().FindImage(CollisionImageName);
}

void ABaseCharacter::SetCharacterRenderOrder()
{
	if (nullptr != GetCurRoom())
	{
		int FloorOrder = 0;
		if (true == CurRoom->GetOnlySecondFloor())
		{
			FloorOrder = static_cast<int>(ERenderOrder::SECOND_FLOOR_OBJ);
		}
		else
		{
			if (ERoomFloor::FLOOR_1F == GetCurRoom()->GetCuRoomFloor())
			{
				FloorOrder = static_cast<int>(ERenderOrder::FIRST_FLOOR_OBJ);
			}
			else
			{
				FloorOrder = static_cast<int>(ERenderOrder::SECOND_FLOOR_OBJ);
			}
		}
		int Padding = GetActorLocation().iY() - GetCurRoom()->GetActorLocation().iY();
		this->SpriteRenderer->SetOrder(FloorOrder + Padding);
	}
}

FVector2D ABaseCharacter::GetDebugLocation(int Index)
{
	FVector2D ResultLocation = GetNoneCameraLocation() + FVector2D(0.0f, DebugMsgLocY * Index);
	return ResultLocation;
}

FVector2D ABaseCharacter::GetDirectionToTargetLocation(FVector2D TargetLocation)
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

FVector2D ABaseCharacter::GetDirectionToThisLocation(FVector2D TargetLocation)
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

FVector2D ABaseCharacter::GetNormalDirectionToTargetLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = TargetLocation - GetActorLocation();
	ResultDir.Normalize();
	return ResultDir;
}

FVector2D ABaseCharacter::GetNormalDirectionToThisLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = GetActorLocation() - TargetLocation;
	ResultDir.Normalize();
	return ResultDir;
}

float ABaseCharacter::GetDistanceToTargetLocation(FVector2D TargetLocation)
{
	return GetActorLocation().DistanceTo(TargetLocation);
}