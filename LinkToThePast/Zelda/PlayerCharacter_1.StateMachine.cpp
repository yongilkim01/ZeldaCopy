#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "HylianKnights.h"
#include "BaseCharacter.h"
#include "EventActor.h"

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
	case EPlayerState::Interact:
		StartInteract();
		break;
	case EPlayerState::LiftIdle:
		StartLiftIdle();
		break;
	case EPlayerState::LiftMove:
		StartLiftMove();
		break;
	default:
		break;
	}

	CurPlayerState = ChangeState;
}

void APlayerCharacter::StartIdle()
{
	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Idle_Left");
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Idle_Up");
	}
	else if (GetCurDirection() == FVector2D::DOWN)
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
	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Run_Right", true);
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Run_Left", true);
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Run_Up", true);
	}
	else if (GetCurDirection() == FVector2D::DOWN)
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
	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Attack_Right", true);
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Attack_Left", true);
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Attack_Up", true);
	}
	else if (GetCurDirection() == FVector2D::DOWN)
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

void APlayerCharacter::StartLiftMove()
{
	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("LiftRunRight");
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("LiftRunLeft");
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("LiftRunUp");
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("LiftRunDown");
	}
}

void APlayerCharacter::StartLiftIdle()
{
	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("LiftIdleRight");
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("LiftIdleLeft");
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("LiftIdleUp");
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("LiftIdleDown");
	}
	else
	{
		MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
		return;
	}
}


void APlayerCharacter::StartInteract()
{
}


void APlayerCharacter::Idle(float DeltaTime)
{
	SetCameraLocationToPlayer();

	if (UEngineInput::GetInst().IsPress('A') == true)
	{
		ChangePlayerDirection(FVector2D::LEFT);
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('D') == true)
	{
		ChangePlayerDirection(FVector2D::RIGHT);
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('W') == true)
	{
		ChangePlayerDirection(FVector2D::UP);
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('S') == true)
	{
		ChangePlayerDirection(FVector2D::DOWN);
		ChangeState(EPlayerState::Move);
		return;
	}

	if (UEngineInput::GetInst().IsPress(VK_LBUTTON) == true &&
		CurPlayerState != EPlayerState::Attack)
	{
		StartAttack();
		CurPlayerState = EPlayerState::Attack;
	}

	if (UEngineInput::GetInst().IsDown('E') == true)
	{
		ChangeState(EPlayerState::Interact);
	}
}

void APlayerCharacter::Move(float DeltaTime)
{
	SetCameraLocationToPlayer();

	if (UEngineInput::GetInst().IsPress('D') == true
		&& MoveDir != FVector2D::RIGHT)
	{
		ChangePlayerDirection(FVector2D::RIGHT);
		MoveDir += FVector2D::RIGHT;
	}
	else if (UEngineInput::GetInst().IsPress('A') == true
		&& MoveDir != FVector2D::LEFT)
	{
		ChangePlayerDirection(FVector2D::LEFT);
		MoveDir += FVector2D::LEFT;
	}

	if (UEngineInput::GetInst().IsPress('S') == true
		&& MoveDir != FVector2D::DOWN)
	{
		ChangePlayerDirection(FVector2D::DOWN);
		MoveDir += FVector2D::DOWN;
	}
	else if (UEngineInput::GetInst().IsPress('W') == true
		&& MoveDir != FVector2D::UP)
	{
		ChangePlayerDirection(FVector2D::UP);
		MoveDir += FVector2D::UP;
	}

	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Run_Left");
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Run_Up");
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Run_Down");
	}

	MoveDir.Normal();

	AddCharacterLocation(MoveDir * DeltaTime * Speed);

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

void APlayerCharacter::LiftMove(float DeltaTime)
{
	SetCameraLocationToPlayer();

	if (UEngineInput::GetInst().IsPress('D') == true
		&& MoveDir != FVector2D::RIGHT)
	{
		ChangePlayerDirection(FVector2D::RIGHT);
		MoveDir += FVector2D::RIGHT;
	}
	else if (UEngineInput::GetInst().IsPress('A') == true
		&& MoveDir != FVector2D::LEFT)
	{
		ChangePlayerDirection(FVector2D::LEFT);
		MoveDir += FVector2D::LEFT;
	}

	if (UEngineInput::GetInst().IsPress('S') == true
		&& MoveDir != FVector2D::DOWN)
	{
		ChangePlayerDirection(FVector2D::DOWN);
		MoveDir += FVector2D::DOWN;
	}
	else if (UEngineInput::GetInst().IsPress('W') == true
		&& MoveDir != FVector2D::UP)
	{
		ChangePlayerDirection(FVector2D::UP);
		MoveDir += FVector2D::UP;
	}

	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("LiftRunRight");
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("LiftRunLeft");
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("LiftRunUp");
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("LiftRunDown");
	}

	MoveDir.Normal();

	AddCharacterLocation(MoveDir * DeltaTime * Speed);

	MoveDir = FVector2D::ZERO;

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{

		ChangeState(EPlayerState::LiftIdle);
	}
}

void APlayerCharacter::Attack(float DeltaTime)
{
	//EffectSoundPlayer = UEngineSound::Play("sword_beam.wav");

	SetCameraLocationToPlayer();
	if (IsAttack == true) return;

	if (GetCurDirection() == FVector2D::RIGHT)
	{
		IsAttack = true;
		ABaseCharacter* Result = dynamic_cast<ABaseCharacter*>(AttackCollisions[0]->CollisionOnce(ECollisionGroup::EnemyBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		IsAttack = true;
		ABaseCharacter* Result = dynamic_cast<ABaseCharacter*>(AttackCollisions[1]->CollisionOnce(ECollisionGroup::EnemyBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		IsAttack = true;
		ABaseCharacter* Result = dynamic_cast<ABaseCharacter*>(AttackCollisions[2]->CollisionOnce(ECollisionGroup::EnemyBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		IsAttack = true;
		ABaseCharacter* Result = dynamic_cast<ABaseCharacter*>(AttackCollisions[3]->CollisionOnce(ECollisionGroup::EnemyBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
}

void APlayerCharacter::Interact(float DetlaTime)
{
	ABaseCharacter::Interact(DetlaTime);

	InteractCollision->SetActive(true);

	OwnedEventActor = dynamic_cast<AEventActor*>(InteractCollision->CollisionOnce(ECollisionGroup::EventTarget));
	if (nullptr != OwnedEventActor)
	{
		OwnedEventActor->Interact(this);

		if (GetCurDirection() == FVector2D::RIGHT)
		{
			SpriteRenderer->ChangeAnimation("LiftRight");
		}
		else if (GetCurDirection() == FVector2D::LEFT)
		{
			SpriteRenderer->ChangeAnimation("LiftLeft");
		}
		else if (GetCurDirection() == FVector2D::UP)
		{
			SpriteRenderer->ChangeAnimation("LiftUp");
		}
		else if (GetCurDirection() == FVector2D::DOWN)
		{
			SpriteRenderer->ChangeAnimation("LiftDown");
		}

		InteractCollision->SetActive(false);
		return;
	}
	ChangeState(EPlayerState::Idle);
}

void APlayerCharacter::KnockBack(float DeltaTime)
{
	AddCharacterLocation(KnockBackDir * DeltaTime * 100.0f);

	KnockBackTime += DeltaTime;

	if (KnockBackTime >= 0.5f)
	{
		ChangeState(EPlayerState::Idle);
		KnockBackTime = 0.0f;
		return;
	}

	FVector2D KncokBackAnimationDir = GetDirectionToTargetLocation(KnockBackDir);

	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("KnockBack_Right");
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("KnockBack_Left");
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("KnockBack_Up");
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("KnockBack_Down");
	}
}

void APlayerCharacter::LiftIdle(float DeltaTime)
{
	SetCameraLocationToPlayer();

	if (UEngineInput::GetInst().IsPress('A') == true)
	{
		ChangePlayerDirection(FVector2D::LEFT);
		ChangeState(EPlayerState::LiftMove);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('D') == true)
	{
		ChangePlayerDirection(FVector2D::RIGHT);
		ChangeState(EPlayerState::LiftMove);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('W') == true)
	{
		ChangePlayerDirection(FVector2D::UP);
		ChangeState(EPlayerState::LiftMove);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('S') == true)
	{
		ChangePlayerDirection(FVector2D::DOWN);
		ChangeState(EPlayerState::LiftMove);
		return;
	}

	if (UEngineInput::GetInst().IsPress('E') == true)
	{
		// TODO : 던지는 상태로 전환
		if (nullptr != OwnedEventActor && true == OwnedEventActor->GetIsControl())
		{
			OwnedEventActor->Throw();
			OwnedEventActor = nullptr;
			ChangeState(EPlayerState::Idle);
		}
	}
}

void APlayerCharacter::EndAttack()
{
	IsAttack = false;
	ChangeState(EPlayerState::Idle);
}

void APlayerCharacter::EndLift()
{
	UEngineDebug::CoreOutPutString("드는 애니메이션 종료");
	ChangeState(EPlayerState::LiftIdle);
}
