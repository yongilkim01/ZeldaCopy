#include "PreCompile.h"
#include "ArmosKngiht_Control.h"
#include "ArmosKnight.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineCoreDebug.h>

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

	CurPhase = 1;
}

void AArmosKngiht_Control::Tick(float DeltaTime)
{
	ABossCharacter::Tick(DeltaTime);

	PrintDebugInfo();

	PhaseTime += DeltaTime;


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
	if (CurPhase == 1)
	{
		BossForces.clear();

		for (int i = 0; i < BossEnemies.size(); i++)
		{
			BossForces.push_back(RotateToDegree(
				CurrentDegree,
				UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half(),
				180.0f));

			CurrentDegree += 60;
		}
	}

	else if (CurPhase == 2)
	{
		BossForces.clear();

		for (int i = 0; i < BossEnemies.size(); i++)
		{
			BossForces.push_back(RotateToDegree(
				CurrentDegree,
				UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half(),
				100.0f));

			CurrentDegree += 60;
		}
	}
	else if (CurPhase == 3)
	{
		BossForces.clear();

		for (int i = 0; i < BossEnemies.size(); i++)
		{
			BossForces.push_back(RotateToDegree(
				CurrentDegree,
				UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half(),
				180.0f));

			CurrentDegree += 60;
		}
	}
	else if (CurPhase == 4)
	{
		BossForces.clear();

		BossForces.push_back({ 144, 144 });
		BossForces.push_back({ 240, 144 });
		BossForces.push_back({ 336, 144 });
		BossForces.push_back({ 432, 144 });
		BossForces.push_back({ 528, 144 });
		BossForces.push_back({ 624, 144 });
	}
	else if (CurPhase == 5)
	{
		BossForces.clear();

		BossForces.push_back({ 144, 520 });
		BossForces.push_back({ 240, 520 });
		BossForces.push_back({ 336, 520 });
		BossForces.push_back({ 432, 520 });
		BossForces.push_back({ 528, 520 });
		BossForces.push_back({ 624, 520 });
	}

	ChangeState(EControlState::MOVE);
}

void AArmosKngiht_Control::Move(float DeltaTime)
{
	if (CurPhase == 1)
	{
		for (int i = 0; i < BossEnemies.size(); i++)
		{
			if (true == CheckDistanceToTarget())
			{
				MoveForcesNextIndex();
			}
			else
			{
				MoveToTargetLocation(BossEnemies[i], BossForces[i], DeltaTime);
			}
		}
	}
	else if (CurPhase == 2)
	{
		for (int i = 0; i < BossEnemies.size(); i++)
		{
			if (true == CheckDistanceToTarget())
			{
				PhaseTime = 0.0f;
				CurPhase++;
				MoveCallCount = 0;
				ChangeState(EControlState::SET);
				return;
			}
			else
			{
				MoveToTargetLocation(BossEnemies[i], BossForces[i], DeltaTime);
			}
		}
	}
	else if (CurPhase == 3)
	{
		for (int i = 0; i < BossEnemies.size(); i++)
		{
			if (true == CheckDistanceToTarget())
			{
				PhaseTime = 0.0f;
				CurPhase++;
				MoveCallCount = 0;
				ChangeState(EControlState::SET);
				return;
			}
			else
			{
				MoveToTargetLocation(BossEnemies[i], BossForces[i], DeltaTime);
			}
		}
	}
	else if(CurPhase == 4)
	{
		for (int i = 0; i < BossEnemies.size(); i++)
		{
			if (true == CheckDistanceToTarget())
			{
				PhaseTime = 0.0f;
				CurPhase++;
				MoveCallCount = 0;
				ChangeState(EControlState::SET);
				return;
			}
			else
			{
				MoveToTargetLocation(BossEnemies[i], BossForces[i], DeltaTime);
			}
		}
	}
	else if (CurPhase == 5)
	{
		for (int i = 0; i < BossEnemies.size(); i++)
		{
			if (true == CheckDistanceToTarget())
			{
				PhaseTime = 0.0f;
				CurPhase = 1;
				MoveCallCount = 0;
				ChangeState(EControlState::SET);
			}
			else
			{
				MoveToTargetLocation(BossEnemies[i], BossForces[i], DeltaTime);
			}
		}
	}
}


FVector2D AArmosKngiht_Control::RotateToDegree(float Degree, FVector2D Location, float H)
{
	FVector2D Result = FVector2D::ZERO;

	Result.X = H * static_cast<float>(std::cos(RADIAN(Degree)));
	Result.Y = H * static_cast<float>(std::sin(RADIAN(Degree)));

	return Result + Location;
}

FVector2D AArmosKngiht_Control::RotateToRadian(float Radian, FVector2D Location, float H)
{
	FVector2D Result = FVector2D::ZERO;

	Result.X = H * Radian;
	Result.Y = H * Radian;

	return Result + Location;
}

bool AArmosKngiht_Control::CheckDistanceToTarget()
{
	for (int i = 0; i < BossEnemies.size(); i++)
	{
		if (BossEnemies[i]->GetActorLocation().DistanceTo(BossForces[i]) > 1.0f)
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
	if (CurPhase == 1 || CurPhase == 2)
	{
		FVector2D ForstForce = BossForces[0];
		for (int i = 0; i < BossForces.size() - 1; i++)
		{
			// TODO: 앞으로 인덱스 이동 구현 예정
			BossForces[i] = BossForces[i + 1];
		}
		BossForces[BossForces.size() - 1] = ForstForce;
		MoveCallCount++;

		if (CurPhase == 1)
		{
			if (MoveCallCount == 6)
			{
				PhaseTime = 0.0f;
				CurPhase++;
				MoveCallCount = 0;
				ChangeState(EControlState::SET);
			}
		}
		else
		{
			if (MoveCallCount == 3)
			{
				PhaseTime = 0.0f;
				CurPhase++;
				MoveCallCount = 0;
				ChangeState(EControlState::SET);
			}
		}
	}
}

FVector2D AArmosKngiht_Control::GetRotateLocation(FVector2D Location, float Degree)
{
	return FVector2D();
}

void AArmosKngiht_Control::SetPhase1Location()
{

}

void AArmosKngiht_Control::PrintDebugInfo()
{

	UEngineDebug::CoreOutPutString("///////////////////////////// Boss Control /////////////////////////////");
	UEngineDebug::CoreOutPutString("Phase Time : " + std::to_string(PhaseTime));
	UEngineDebug::CoreOutPutString("Cur Phase : " + std::to_string(CurPhase));

	switch (CurControlState)
	{
	case EControlState::SET:
		UEngineDebug::CoreOutPutString("Cur control state : SET");
		break;
	case EControlState::MOVE:
		UEngineDebug::CoreOutPutString("Cur control state : MOVE");
		break;
	default:
		break;
	}
}
