#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "HylianKnights.h"
#include "BaseCharacter.h"
#include "EventActor.h"
#include "PlayerDataManager.h"
#include "WeaponItem.h"
#include "Grass.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/Collision2D.h>

void APlayerCharacter::ChangeState(EPlayerState ChangeState)
{
	//if (CurPlayerState == ChangeState) return;

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
	case EPlayerState::Skill:
		StartSkill();
		break;
	case EPlayerState::KnockBack:
		StartKnockBack();
		break;
	case EPlayerState::Interact:
		StartInteract();
		break;
	case EPlayerState::Lift:
		StartLift();
		break;
	case EPlayerState::LiftIdle:
		StartLiftIdle();
		break;
	case EPlayerState::LiftMove:
		StartLiftMove();
		break;
	case EPlayerState::Sleep:
		StartSleep();
		break;
	case EPlayerState::WakeUp:
		StartWakeUp();
		break;
	case EPlayerState::Fall:
		StartFall();
		break;
	case EPlayerState::TurnFall:
		StartTurnFall();
		break;
	case EPlayerState::SwordGet:
		StartSwordGet();
		break;
	default:
		break;
	}

	CurPlayerState = ChangeState;
}

void APlayerCharacter::StartIdle()
{
	if (true == PlayerDataManager::GetInstance().IsEquipWeapon())
	{
		if (GetCurDirection() == FVector2D::RIGHT)
		{
			SpriteRenderer->ChangeAnimation("ShieldIdleRight");
		}
		else if (GetCurDirection() == FVector2D::LEFT)
		{
			SpriteRenderer->ChangeAnimation("ShieldIdleLeft");
		}
		else if (GetCurDirection() == FVector2D::UP)
		{
			SpriteRenderer->ChangeAnimation("ShieldIdleUp");
		}
		else if (GetCurDirection() == FVector2D::DOWN)
		{
			SpriteRenderer->ChangeAnimation("ShieldIdleDown");
		}
		else
		{
			MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
			return;
		}
	}
	else
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
}

void APlayerCharacter::StartMove()
{
	if (true == PlayerDataManager::GetInstance().IsEquipWeapon())
	{
		if (GetCurDirection() == FVector2D::RIGHT)
		{
			SpriteRenderer->ChangeAnimation("ShieldMoveRight");
		}
		else if (GetCurDirection() == FVector2D::LEFT)
		{
			SpriteRenderer->ChangeAnimation("ShieldMoveLeft");
		}
		else if (GetCurDirection() == FVector2D::UP)
		{
			SpriteRenderer->ChangeAnimation("ShieldMoveUp");
		}
		else if (GetCurDirection() == FVector2D::DOWN)
		{
			SpriteRenderer->ChangeAnimation("ShieldMoveDown");
		}
		else
		{
			MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
			return;
		}
	}
	else
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
	}
}

void APlayerCharacter::StartAttack()
{
	EffectSoundPlayer = UEngineSound::Play("fighter sword 2.wav");

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

void APlayerCharacter::StartSkill()
{
	if (true == PlayerDataManager::GetInstance().GetWeaponActiveToIndex(1))
	{
		if (GetCurDirection() == FVector2D::RIGHT)
		{
			SpriteRenderer->ChangeAnimation("BowRight", true);
		}
		else if (GetCurDirection() == FVector2D::LEFT)
		{
			SpriteRenderer->ChangeAnimation("BowLeft", true);
		}
		else if (GetCurDirection() == FVector2D::UP)
		{
			SpriteRenderer->ChangeAnimation("BowUp", true);
		}
		else if (GetCurDirection() == FVector2D::DOWN)
		{
			SpriteRenderer->ChangeAnimation("BowDown", true);
		}
		else
		{
			MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
			return;
		}
	}
}

void APlayerCharacter::StartKnockBack()
{
	CurPlayerState = EPlayerState::KnockBack;
}

void APlayerCharacter::StartLift()
{
	if (GetCurDirection() == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("LiftRight", true);
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("LiftLeft", true);
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("LiftUp", true);
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("LiftDown", true);
	}
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

void APlayerCharacter::StartSleep()
{
	SpriteRenderer->ChangeAnimation("LinkSleep");
}

void APlayerCharacter::StartWakeUp()
{
	SpriteRenderer->ChangeAnimation("LinkWakeUp");
}

void APlayerCharacter::StartFall()
{
	SpriteRenderer->ChangeAnimation("Fall");
}

void APlayerCharacter::StartTurnFall()
{
	SpriteRenderer->ChangeAnimation("TurnFall");
}

void APlayerCharacter::StartSwordGet()
{
	SpriteRenderer->ChangeAnimation("SwordGet");
}


void APlayerCharacter::StartInteract()
{
	InteractCollision->SetActive(true);

	//OwnedEventActor = dynamic_cast<AEventActor*>(InteractCollision->CollisionOnce(ECollisionGroup::EventTarget));

	std::vector<AActor*> Results = InteractCollision->CollisionAll(ECollisionGroup::EventTarget);

	for (int i = 0; i < Results.size(); i++)
	{
		AEventActor* Result = dynamic_cast<AEventActor*>(Results[i]);

		if (nullptr != Result)
		{
			if (true == Result->GetIsEquipalbe())
			{
				OwnedEventActor = Result;

				if (nullptr != OwnedEventActor)
				{
					int Result = OwnedEventActor->Interact(this);

					if (1 == Result)
					{
						ChangeState(EPlayerState::Lift);
						InteractCollision->SetActive(false);
						return;
					}
				}
			}
			else
			{
				Result->Interact(this);
			}
		}
	}

	InteractCollision->SetActive(false);
	ChangeState(EPlayerState::Idle);
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

	if (true == PlayerDataManager::GetInstance().IsEquipWeapon() &&
		UEngineInput::GetInst().IsDown(VK_LBUTTON) == true &&
		CurPlayerState != EPlayerState::Attack)
	{
		StartAttack();
		CurPlayerState = EPlayerState::Attack;
	}
	else if (UEngineInput::GetInst().IsDown(VK_RBUTTON) == true &&
		CurPlayerState != EPlayerState::Skill)
	{
		ChangeState(EPlayerState::Skill);
	}

	if (UEngineInput::GetInst().IsDown('E') == true)
	{
		//ChangeState(EPlayerState::Interact);
		CheckInteract();
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

	if (true == PlayerDataManager::GetInstance().IsEquipWeapon())
	{
		if (GetCurDirection() == FVector2D::RIGHT)
		{
			SpriteRenderer->ChangeAnimation("ShieldMoveRight");
		}
		else if (GetCurDirection() == FVector2D::LEFT)
		{
			SpriteRenderer->ChangeAnimation("ShieldMoveLeft");
		}
		else if (GetCurDirection() == FVector2D::UP)
		{
			SpriteRenderer->ChangeAnimation("ShieldMoveUp");
		}
		else if (GetCurDirection() == FVector2D::DOWN)
		{
			SpriteRenderer->ChangeAnimation("ShieldMoveDown");
		}
		else
		{
			MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
			return;
		}
	}
	else
	{
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

	if (true == PlayerDataManager::GetInstance().IsEquipWeapon() &&
		true == UEngineInput::GetInst().IsDown(VK_LBUTTON) &&
		EPlayerState::Attack != CurPlayerState)
	{
		StartAttack();
		CurPlayerState = EPlayerState::Attack;
	}
	else if (UEngineInput::GetInst().IsDown(VK_RBUTTON) == true &&
		CurPlayerState != EPlayerState::Skill)
	{
		ChangeState(EPlayerState::Skill);
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
	SetCameraLocationToPlayer();
	if (IsAttack == true) return;

	IsAttack = true;

	std::vector<AActor*> Results = AttackCollision->CollisionAll(ECollisionGroup::EnemyBody);

	for (int i = 0; i < Results.size(); i++)
	{
		ABaseCharacter* Result = dynamic_cast<ABaseCharacter*>(Results[i]);

		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}

	std::vector<AActor*> EvenvActors = AttackCollision->CollisionAll(ECollisionGroup::NOTMOVEABLE);

	for (int i = 0; i < EvenvActors.size(); i++)
	{
		AGrass* Result = dynamic_cast<AGrass*>(EvenvActors[i]);

		if (nullptr != Result)
		{
			Result->DestoryEventActor();
		}
	}
}

void APlayerCharacter::Skill(float DeltaTime)
{
	if (0 != PlayerDataManager::GetInstance().GetWeaponCount() &&
		false == IsAttack)
	{
		WeaponItemes[PlayerDataManager::GetInstance().GetSelectWeapon()]->Action(DeltaTime);
		IsAttack = true;
	}
}

void APlayerCharacter::Interact(float DetlaTime)
{

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

void APlayerCharacter::Lift(float DeltaTime)
{
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

void APlayerCharacter::Sleep(float DeltaTime)
{
}

void APlayerCharacter::WakeUp(float DeltaTime)
{
}

void APlayerCharacter::Fall(float DeltaTime)
{
}

void APlayerCharacter::TurnFall(float DeltaTime)
{
	SetCameraLocationToPlayer();
}

void APlayerCharacter::GetSword(float DeltaTime)
{
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
