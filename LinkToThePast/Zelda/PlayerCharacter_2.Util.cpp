#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "HylianKnights.h"
#include "PlayerDataManager.h"

#include <EngineCore/EngineAPICore.h>

void APlayerCharacter::TakeDamage(int Damage, ABaseCharacter* Character)
{
	if (CurPlayerState == EPlayerState::KnockBack) return;

	PlayerDataManager::GetInstance().AddHP(-Damage);

	this->KnockBackDir = GetActorLocation() - Character->GetActorLocation();
	SetCurDirection(GetDirectionToTargetLocation(Character->GetActorLocation()));
	KnockBackDir.Normalize();

	ChangeState(EPlayerState::KnockBack);

	TimeEventer.PushEvent(0.0f, [this] ()
		{
			HitCollision->SetActive(false);
		}
	, false, false);

	TimeEventer.PushEvent(3.0f, [this]()
		{
			HitCollision->SetActive(true);
		}
	, false, false);

	//if (CurrentHP < 0)
	//{
	//	PrevPlayerState = CurPlayerState;
	//	CurPlayerState = EPlayerState::KnockBack;
	//}

	//PrevPlayerState = CurPlayerState;
	//CurPlayerState = EPlayerState::KnockBack;
}

void APlayerCharacter::ChangePlayerDirection(FVector2D Dir)
{
	SetCurDirection(Dir);

	InteractCollision->SetComponentLocation(Dir * 25.0f);
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
	GetWorld()->SetCameraLocation(GetActorLocation() - WindowSize.Half());

	DebugOn();
}

void APlayerCharacter::PlayerGroundCheck(FVector2D _MovePos)
{
	IsMove = false;
	IsGround = false;
	if (nullptr != GetCollisionImage())
	{
		// 픽셀충돌에서 제일 중요한건 애초에 박히지 않는것이다.
		FVector2D NextPos = GetActorLocation() + _MovePos;
		UColor Color = GetCollisionImage()->GetColor(NextPos, UColor::BLACK);
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

void APlayerCharacter::SetPlayerStateToIdle()
{
	SpriteRenderer->ChangeAnimation("Idle_Down");
	CurPlayerState = EPlayerState::Idle;
}

void APlayerCharacter::SetCameraLocationToPlayer()
{
	if (GetCurRoom() != nullptr)
	{
		FVector2D CameraMovePos = GetTransform().Location + GetWorld()->GetCameraPivot();

		if (CameraMovePos.iX() < GetCurRoom()->LeftTopPos.iX())
		{
			CameraMovePos.X = GetCurRoom()->LeftTopPos.X;
		}
		if (CameraMovePos.iY() < GetCurRoom()->LeftTopPos.iY())
		{
			CameraMovePos.Y = GetCurRoom()->LeftTopPos.Y;
		}
		if (GetCurRoom()->RightBottomPos.iX() < CameraMovePos.iX() + UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X)
		{
			CameraMovePos.X = GetCurRoom()->RightBottomPos.X - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X;
		}
		if (GetCurRoom()->RightBottomPos.iY() < CameraMovePos.iY() + UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y)
		{
			CameraMovePos.Y = GetCurRoom()->RightBottomPos.Y - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y;
		}

		GetWorld()->SetCameraLocation(CameraMovePos);
	}
}