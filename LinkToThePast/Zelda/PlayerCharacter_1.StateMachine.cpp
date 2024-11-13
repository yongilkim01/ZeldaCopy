#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "HylianKnights.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/Collision2D.h>

void APlayerCharacter::ChangeState(EPlayerState ChangeState)
{
	switch (ChangeState)
	{
	case EPlayerState::Idle:
		StartIdle();
		break;
	case EPlayerState::Move:
		StartMove();
		break;
	case EPlayerState::Attack:
		StartAttack();
		break;
	case EPlayerState::KnockBack:
		StartKnockBack();
		break;
	default:
		break;
	}

	CurPlayerState = ChangeState;
}

void APlayerCharacter::StartIdle()
{
	if (CurDir == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}
	else if (CurDir == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Idle_Left");
	}
	else if (CurDir == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Idle_Up");
	}
	else if (CurDir == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Idle_Down");
	}
	else
	{
		MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
		return;
	}
}

void APlayerCharacter::StartMove()
{
	if (CurDir == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Run_Right", true);
	}
	else if (CurDir == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Run_Left", true);
	}
	else if (CurDir == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Run_Up", true);
	}
	else if (CurDir == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Run_Down", true);
	}
	else
	{
		MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
		return;
	}

	CurPlayerState = EPlayerState::Move;
}

void APlayerCharacter::StartAttack()
{
	if (CurDir == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Attack_Right", true);
	}
	else if (CurDir == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Attack_Left", true);
	}
	else if (CurDir == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Attack_Up", true);
	}
	else if (CurDir == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Attack_Down", true);
	}
	else
	{
		MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
		return;
	}

	CurPlayerState = EPlayerState::Attack;
}

void APlayerCharacter::StartKnockBack()
{
	CurPlayerState = EPlayerState::KnockBack;
}

void APlayerCharacter::Idle(float DeltaTime)
{
	SetCameraLocationToPlayer();

	if (UEngineInput::GetInst().IsPress('A') == true)
	{
		CurDir = FVector2D::LEFT;
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('D') == true)
	{
		CurDir = FVector2D::RIGHT;
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('W') == true)
	{
		CurDir = FVector2D::UP;
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('S') == true)
	{
		CurDir = FVector2D::DOWN;
		ChangeState(EPlayerState::Move);
		return;
	}

	if (UEngineInput::GetInst().IsPress(VK_LBUTTON) == true &&
		CurPlayerState != EPlayerState::Attack)
	{
		StartAttack();
		CurPlayerState = EPlayerState::Attack;
	}
}

void APlayerCharacter::Move(float DeltaTime)
{
	SetCameraLocationToPlayer();

	if (UEngineInput::GetInst().IsPress('D') == true
		&& MoveDir != FVector2D::RIGHT)
	{
		CurDir = FVector2D::RIGHT;
		MoveDir += FVector2D::RIGHT;
	}
	else if (UEngineInput::GetInst().IsPress('A') == true
		&& MoveDir != FVector2D::LEFT)
	{
		CurDir = FVector2D::LEFT;
		MoveDir += FVector2D::LEFT;
	}

	if (UEngineInput::GetInst().IsPress('S') == true
		&& MoveDir != FVector2D::DOWN)
	{
		CurDir = FVector2D::DOWN;
		MoveDir += FVector2D::DOWN;
	}
	else if (UEngineInput::GetInst().IsPress('W') == true
		&& MoveDir != FVector2D::UP)
	{
		CurDir = FVector2D::UP;
		MoveDir += FVector2D::UP;
	}

	if (CurDir == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
	}
	else if (CurDir == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Run_Left");
	}
	else if (CurDir == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Run_Up");
	}
	else if (CurDir == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Run_Down");
	}

	MoveDir.Normal();

	if (CollisionImage != nullptr)
	{
		// 픽셀충돌에서 제일 중요한건 애초에 박히지 않는것이다.
		FVector2D NextPos = GetActorLocation() + MoveDir * DeltaTime * Speed;
		NextPos -= CurRoom->GetActorLocation();
		UColor Color = CollisionImage->GetColor(NextPos, UColor::PINK);
		if (Color != UColor::PINK)
		{
			AddActorLocation(MoveDir * DeltaTime * Speed);
		}

		if (Color == UColor::ROOM_UPSTAIRS && CurRoom->GetIsSecondFloor())
		{
			//AddActorLocation(MoveDir * DeltaTime * (Speed * 0.5f));
			CurRoom->SetCulWinImageTo2F();
			this->CurRoomFloor = ERoomFloor::FLOOR_2F;
			this->CollisionImage = CurRoom->GetColWinImage2F();
			this->SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::PLAYER) + 100);
		}
		else if (Color == UColor::ROOM_DOWNSTAIRS && CurRoom->GetIsSecondFloor())
		{
			//AddActorLocation(MoveDir * DeltaTime * (Speed * 0.5f));
			CurRoom->SetCulWinImageTo1F();
			this->CurRoomFloor = ERoomFloor::FLOOR_1F;
			this->CollisionImage = CurRoom->GetColWinImage1F();
			SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::PLAYER));
		}
	}

	MoveDir = FVector2D::ZERO;

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{

		ChangeState(EPlayerState::Idle);
	}

	if (UEngineInput::GetInst().IsPress(VK_LBUTTON) == true &&
		CurPlayerState != EPlayerState::Attack)
	{
		StartAttack();
		CurPlayerState = EPlayerState::Attack;
	}
}

void APlayerCharacter::Attack(float DeltaTime)
{
	SetCameraLocationToPlayer();
	if (IsAttack == true) return;

	if (this->CurDir == FVector2D::RIGHT)
	{
		IsAttack = true;
		AHylianKnights* Result = dynamic_cast<AHylianKnights*>(AttackCollisions[0]->CollisionOnce(ECollisionGroup::EnemyBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10);
		}
	}
	else if (this->CurDir == FVector2D::LEFT)
	{
		IsAttack = true;
		AHylianKnights* Result = dynamic_cast<AHylianKnights*>(AttackCollisions[1]->CollisionOnce(ECollisionGroup::EnemyBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10);
		}
	}
	else if (this->CurDir == FVector2D::DOWN)
	{
		IsAttack = true;
		AHylianKnights* Result = dynamic_cast<AHylianKnights*>(AttackCollisions[2]->CollisionOnce(ECollisionGroup::EnemyBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10);
		}
	}
	else if (this->CurDir == FVector2D::UP)
	{
		IsAttack = true;
		AHylianKnights* Result = dynamic_cast<AHylianKnights*>(AttackCollisions[3]->CollisionOnce(ECollisionGroup::EnemyBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10);
		}
	}
}

void APlayerCharacter::KnockBack(float DeltaTime)
{
	AddActorLocation(KnockBackDir * DeltaTime * 1000.0f);
}

void APlayerCharacter::EndAttack()
{
	IsAttack = false;
	ChangeState(EPlayerState::Idle);
}