#include "PreCompile.h"
#include "ArmosKngiht_Control.h"
#include "ArmosKnight.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>

AArmosKngiht_Control::AArmosKngiht_Control()
{
	
}

AArmosKngiht_Control::~AArmosKngiht_Control()
{
}

void AArmosKngiht_Control::BeginPlay()
{
	ABossCharacter::BeginPlay();

	BossForces.reserve(10);

	BossForces.push_back({ 235, 231 });
	BossForces.push_back({ 380, 231 });
	BossForces.push_back({ 525, 231 });
	BossForces.push_back({ 235, 340 });
	BossForces.push_back({ 380, 340 });
	BossForces.push_back({ 525, 340 });

	FVector2D WindowHalfSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half();

	for (int i = 0; i < 6; i++)
	{
		AArmosKnight* ArmosKnight = GetWorld()->SpawnActor<AArmosKnight>();
		ArmosKnight->SetActorLocation(WindowHalfSize);
		ArmosKnight->SetActorLocation(BossForces[i]);
		BossEnemies.push_back(ArmosKnight);

	}

	BossForces.clear();

	for (int i = 0; i < BossEnemies.size(); i++)
	{
		BossForces.push_back(RotateToDegree(
			CurrentDegree,
			UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half(),
			180.0f));

		CurrentDegree += 60;
	}

	ChangeState(EControlState::MOVE);
}

void AArmosKngiht_Control::Tick(float DeltaTime)
{
	ABossCharacter::Tick(DeltaTime);

	switch (CurControlState)
	{
	case EControlState::SET:
		Set(DeltaTime);
		break;
	case EControlState::MOVE:
		Move(DeltaTime);
		break;
	default:
		break;
	}

}

/**
 *	30    90    150    210    270    330
 */

void AArmosKngiht_Control::Set(float DeltaTime)
{
	MoveForcesNextIndex();

	ChangeState(EControlState::MOVE);
}

void AArmosKngiht_Control::Move(float DeltaTime)
{
	for (int i = 0; i < BossEnemies.size(); i++)
	{
		if (true == CheckDistanceToTarget())
		{
			ChangeState(EControlState::SET);
			return;
		}
		else
		{
			MoveToTargetLocation(BossEnemies[i], BossForces[i], DeltaTime);
		}
	}
}


FVector2D AArmosKngiht_Control::RotateToDegree(float Degree, FVector2D Location, float H)
{
	FVector2D Result = FVector2D::ZERO;

	Result.X = H * std::cos(RADIAN(Degree));
	Result.Y = H * std::sin(RADIAN(Degree));

	return Result + Location;
}

bool AArmosKngiht_Control::CheckDistanceToTarget()
{
	for (int i = 0; i < BossEnemies.size(); i++)
	{
		if (BossEnemies[i]->GetActorLocation().DistanceTo(BossForces[i]) > 10.0f)
		{
			return false;
		}
	}
	return true;
}

void AArmosKngiht_Control::MoveToTargetLocation(AActor* Actor, FVector2D TargetLocation, float DeltaTime)
{
	FVector2D MoveDir = TargetLocation - Actor->GetActorLocation();
	MoveDir.Normalize();

	Actor->AddActorLocation(MoveDir * this->Speed * DeltaTime);
}

void AArmosKngiht_Control::ChangeState(EControlState ControlState)
{
	this->CurControlState = ControlState;
}

void AArmosKngiht_Control::MoveForcesNextIndex()
{
	FVector2D ForstForce = BossForces[0];
	for (int i = 0; i < BossForces.size() - 1; i++)
	{
		// TODO: 앞으로 인덱스 이동 구현 예정
		BossForces[i] = BossForces[i + 1];
	}
	BossForces[BossForces.size() -  1] = ForstForce;
}
