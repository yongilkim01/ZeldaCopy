#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "HylianKnights.h"

#include <EngineCore/EngineAPICore.h>

void APlayerCharacter::TakeDamage(int Damage, AEnemyCharacter* EnemyCharacter)
{
	if (CurPlayerState == EPlayerState::KnockBack) return;

	CurrentHP -= Damage;

	this->KnockBackDir = GetActorLocation() - EnemyCharacter->GetActorLocation();
	KnockBackDir.Normalize();

	ChangeState(EPlayerState::KnockBack);

	//if (CurrentHP < 0)
	//{
	//	PrevPlayerState = CurPlayerState;
	//	CurPlayerState = EPlayerState::KnockBack;
	//}

	//PrevPlayerState = CurPlayerState;
	//CurPlayerState = EPlayerState::KnockBack;
}

void APlayerCharacter::SetCurRoom(ARoom* Room)
{
	if (this->CurRoom != nullptr)
	{
		this->CurRoom->SetPlayer(nullptr);
		this->CurRoom = nullptr;
		this->CollisionImage = nullptr;
	}

	this->CurRoom = Room;
	this->CurRoom->SetPlayer(this);

	if (CurRoom->GetIsSecondFloor())
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
	else
	{
		SetCollisionImage(CurRoom->GetColWinImage1F()->GetName());
	}
}

FVector2D APlayerCharacter::GetDirectionToTargetLocation(FVector2D TargetLocation)
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

void APlayerCharacter::PlayerCameraCheck()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPos(GetActorLocation() - WindowSize.Half());

	DebugOn();
}

void APlayerCharacter::PlayerGroundCheck(FVector2D _MovePos)
{
	IsMove = false;
	IsGround = false;
	if (nullptr != CollisionImage)
	{
		// 픽셀충돌에서 제일 중요한건 애초에 박히지 않는것이다.
		FVector2D NextPos = GetActorLocation() + _MovePos;
		UColor Color = CollisionImage->GetColor(NextPos, UColor::BLACK);
		if (Color == UColor::WHITE)
		{
			IsMove = true;
		}
		else if (Color == UColor::BLACK)
		{
			IsGround = true;
		}
	}
}
void APlayerCharacter::Gravity(float _DeltaTime)
{
	if (false == IsGround)
	{
		GravityForce += FVector2D::DOWN * _DeltaTime * 0.1f;
	}
	else {
		GravityForce = FVector2D::ZERO;
	}
	// 상시 
	AddActorLocation(GravityForce);
}

void APlayerCharacter::RunSoundPlay()
{

}

void APlayerCharacter::SetCollisionImage(std::string_view CollisionImageName)
{
	CollisionImage = UImageManager::GetInst().FindImage(CollisionImageName);
}

void APlayerCharacter::SetPlayerStateToIdle()
{
	SpriteRenderer->ChangeAnimation("Idle_Down");
	CurPlayerState = EPlayerState::Idle;
}

void APlayerCharacter::SetCameraLocationToPlayer()
{
	if (CurRoom != nullptr)
	{
		FVector2D CameraMovePos = GetTransform().Location + GetWorld()->GetCameraPivot();

		if (CameraMovePos.iX() < CurRoom->LeftTopPos.iX())
		{
			CameraMovePos.X = CurRoom->LeftTopPos.X;
		}
		if (CameraMovePos.iY() < CurRoom->LeftTopPos.iY())
		{
			CameraMovePos.Y = CurRoom->LeftTopPos.Y;
		}
		if (CurRoom->RightBottomPos.iX() < CameraMovePos.iX() + UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X)
		{
			CameraMovePos.X = CurRoom->RightBottomPos.X - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X;
		}
		if (CurRoom->RightBottomPos.iY() < CameraMovePos.iY() + UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y)
		{
			CameraMovePos.Y = CurRoom->RightBottomPos.Y - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y;
		}

		GetWorld()->SetCameraPos(CameraMovePos);
	}
}