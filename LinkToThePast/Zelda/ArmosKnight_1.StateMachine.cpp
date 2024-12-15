#include "PreCompile.h"
#include "ArmosKnight.h"
#include "PlayerCharacter.h"

#include <EngineCore/SpriteRenderer.h>

void AArmosKnight::Stay(float DeltaTime)
{
}

void AArmosKnight::Move(float DeltaTime)
{
	// 보스 컨트롤이 지정해준 위치로 이동
	{
		FVector2D MoveDir = TargetLocation - GetActorLocation();
		MoveDir.Normalize();
		AddActorLocation(MoveDir * 300.0f * DeltaTime);
	}
	// 자체 점프
	{
		// 중력
		CurJumpPower += FVector2D::DOWN * 2000.0f * DeltaTime;
		SpriteRenderer->AddComponentLocation(CurJumpPower * DeltaTime);

		if (0.0f <= SpriteRenderer->GetComponentLocation().Y)
		{
			SoundPlayer = UEngineSound::Play("ram.wav");
			SoundPlayer.SetVolume(0.5f);
			CurJumpPower = FVector2D::UP * 500.0f;
		}
	}

	CheckAttackCollision();
}

void AArmosKnight::Knockback(float DeltaTime)
{
	if (KnockBackCount > 50 || TargetCharacter == nullptr)
	{
		//CurBossState = PrevEnemyState;
		KnockBackCount = 0;
		ChangeState(PrevBossState);
		return;
	}

	FVector2D PlayerLocation = this->TargetCharacter->GetActorLocation();

	AddCharacterLocation(TargetCharacter->GetCurDirection() * DeltaTime * 1000.0f);
	KnockBackCount++;

	// 자체 점프
	{
		// 중력
		CurJumpPower += FVector2D::DOWN * 2000.0f * DeltaTime;
		SpriteRenderer->AddComponentLocation(CurJumpPower * DeltaTime);

		if (0.0f <= SpriteRenderer->GetComponentLocation().Y)
		{
			SoundPlayer = UEngineSound::Play("ram.wav");
			CurJumpPower = FVector2D::UP * 500.0f;
		}
	}
}

void AArmosKnight::BerserkWait(float DeltaTime)
{
	CoolTime += DeltaTime;

	if (CoolTime >= 1.5f)
	{
		CoolTime = 0.0f;
		ChangeState(EBossState::BERSERK_MOVE);
		TargetLocation = TargetCharacter->GetActorLocation() - FVector2D(0.0f, 150.0f);
	}
}

void AArmosKnight::BerserkMove(float DeltaTime)
{
	// 관리자가 지정해준 위치로 이동
	{
		FVector2D MoveDir = TargetLocation - GetActorLocation();
		MoveDir.Normalize();
		AddActorLocation(MoveDir * 700.0f * DeltaTime);

		if (GetActorLocation().DistanceTo(TargetLocation) < 5.0f)
		{
			SetActorLocation(TargetLocation + FVector2D(0.0f, 150.0f));
			SetBossComponentLocation({ 0.0f, -150.0f });
			ChangeState(EBossState::BERSERK_ATTACK);
			TargetLocation = FVector2D::ZERO;
			AttackCollision->SetActive(true);
		}
	}
}

void AArmosKnight::BerserkAttack(float DeltaTime)
{
	AddBossComponentLocation(FVector2D::DOWN * 1500.0f * DeltaTime);
	CheckAttackCollision();

	if (SpriteRenderer->GetComponentLocation().DistanceTo(TargetLocation) < 5.0f)
	{
		SoundPlayer = UEngineSound::Play("ram.wav");
		SetBossComponentLocation(TargetLocation);
		ChangeState(EBossState::BERSERK_WAIT);
		AttackCollision->SetActive(false);
	}
}

void AArmosKnight::ChangeState(EBossState BossState)
{
	switch (BossState)
	{
	case EBossState::NONE:
		break;
	case EBossState::MOVE:
		SpriteRenderer->ChangeAnimation("Move");
		break;
	case EBossState::KNOCKBACK:
		PrevBossState = CurBossState;
		break;
	case EBossState::BERSERK_WAIT:
		AttackCollision->SetActive(false);
		SpriteRenderer->ChangeAnimation("Berserk");
		SpriteRenderer->SetComponentLocation({ 0.0f, 0.0f });
		this->IsManage = false;
		break;
	case EBossState::BERSERK_MOVE:
		break;
	case EBossState::BERSERK_ATTACK:
		break;
	default:
		break;
	}

	this->CurBossState = BossState;

}