#include "PreCompile.h"
#include "ArmosKngiht_Control.h"
#include "PlayerCharacter.h"
#include "ArmosKnight.h"
#include "Room.h"
#include "SoundManager.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineCoreDebug.h>

AArmosKngiht_Control::AArmosKngiht_Control()
{
	BodyCollision = CreateDefaultSubObject<UCollision2D>();
	BodyCollision->SetComponentLocation({ 0, 10 });
	BodyCollision->SetComponentScale({ 50,55 });
	BodyCollision->SetCollisionGroup(ECollisionGroup::MOVEABLE);
	BodyCollision->SetActive(true);
}

AArmosKngiht_Control::~AArmosKngiht_Control()
{
}

void AArmosKngiht_Control::BeginPlay()
{
	ABossCharacter::BeginPlay();

	BossForces.reserve(10);

	ChangeState(EControlState::STAY);
}

void AArmosKngiht_Control::Tick(float DeltaTime)
{
	ABossCharacter::Tick(DeltaTime);

	PrintDebugInfo();

	PhaseTime += DeltaTime;


	switch (CurControlState)
	{
	case EControlState::STAY:
		Stay(DeltaTime);
		break;
	case EControlState::SET:
		Set(DeltaTime);
		break;
	case EControlState::MOVE:
		Move(DeltaTime);
		break;
	case EControlState::END:
		End(DeltaTime);
		break;
	default:
		break;
	}

	if (EControlState::SET == CurControlState ||
		EControlState::MOVE == CurControlState)
	{
		std::list<AArmosKnight*>::iterator StartIter = BossEnemies.begin();
		std::list<AArmosKnight*>::iterator EndIter = BossEnemies.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AArmosKnight* CurArmosKnight = *StartIter;
			int ManageIndex = CurArmosKnight->GetManageIndex();
			if (CurArmosKnight->GetIsManage())
			{
				CurArmosKnight->SetTargetLocation(BossForces[ManageIndex]);
			}
		}
	}
}

void AArmosKngiht_Control::StartStay()
{
	BossForces.push_back({ 235, 231 });
	BossForces.push_back({ 380, 231 });
	BossForces.push_back({ 525, 231 });
	BossForces.push_back({ 235, 340 });
	BossForces.push_back({ 380, 340 });
	BossForces.push_back({ 525, 340 });

	for (int i = 0; i < 6; i++)
	{
		AArmosKnight* ArmosKnight = GetWorld()->SpawnActor<AArmosKnight>();
		ArmosKnight->SetActorLocation(BossForces[i]);
		ArmosKnight->SetManager(this);
		ArmosKnight->SetPlayerCharacter(PlayerCharacter);
		ArmosKnight->SetManageIndex(i);
		ArmosKnight->SetCurRoom(GetCurRoom(), false);
		ArmosKnight->SetTargetLocation(BossForces[i]);
		BossEnemies.push_back(ArmosKnight);

	}

	CurPhase = 1;

	USoundManager::GetInstance().PlayBGMSound("BossBGM1.mp3");
}

void AArmosKngiht_Control::Stay(float DeltaTime)
{
	CurTime += DeltaTime;

	if (CurTime >= 4.0f)
	{
		std::list<AArmosKnight*>::iterator StartIter = BossEnemies.begin();
		std::list<AArmosKnight*>::iterator EndIter = BossEnemies.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AArmosKnight* CurArmosKnight = *StartIter;
			CurArmosKnight->ChangeState(EBossState::MOVE);
		}

		USoundManager::GetInstance().StopBGMSound();
		USoundManager::GetInstance().PlayBGMSound("BossBGM2.mp3");
		ChangeState(EControlState::SET);
	}
}

/**
 *	30    90    150    210    270    330
 */

void AArmosKngiht_Control::StartSet()
{
}

void AArmosKngiht_Control::Set(float DeltaTime)
{
	if (CurPhase == 1)
	{
		BossForces.clear();

		for (int i = 0; i < 6; i++)
		{
			BossForces.push_back(RotateToDegree(
				CurrentDegree,
				UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half(),
				180.0f));

			CurrentDegree += 60;
		}
	}
	else if (CurPhase == 3)
	{
		BossForces.clear();

		for (int i = 0; i < 6; i++)
		{
			BossForces.push_back(RotateToDegree(
				CurrentDegree,
				UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half(),
				100.0f));

			CurrentDegree += 60;
		}
	}
	else if (CurPhase == 5)
	{
		BossForces.clear();

		for (int i = 0; i < 6; i++)
		{
			BossForces.push_back(RotateToDegree(
				CurrentDegree,
				UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half(),
				180.0f));

			CurrentDegree += 60;
		}
	}
	else if (CurPhase == 6)
	{
		BossForces.clear();

		BossForces.push_back({ 144, 144 });
		BossForces.push_back({ 240, 144 });
		BossForces.push_back({ 336, 144 });
		BossForces.push_back({ 432, 144 });
		BossForces.push_back({ 528, 144 });
		BossForces.push_back({ 624, 144 });
	}
	else if (CurPhase == 7)
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

void AArmosKngiht_Control::StartMove()
{
}

void AArmosKngiht_Control::Move(float DeltaTime)
{
	// 큰 원으로 이동
	if (CurPhase == 1)
	{
		if (PhaseTime >= 1.2f)
		{
			CurPhase++;
			PhaseTime = 0.0f;
		}
	}
	// 큰 원을 회전
	else if (CurPhase == 2)
	{
		if (PhaseTime >= 0.6f)
		{
			PhaseTime = 0.0f;
			MoveForcesNextIndex();
			return;
		}
	}
	// 작은 원으로 이동
	else if (CurPhase == 3)
	{
		if (PhaseTime >= 0.4f)
		{
			CurPhase++;
			PhaseTime = 0.0f;
		}
	}
	// 작은 원을 회전
	else if (CurPhase == 4)
	{
		if (PhaseTime >= 0.6f)
		{
			PhaseTime = 0.0f;
			MoveForcesNextIndex();
			return;
		}
	}
	// 큰 원으로 이동
	else if (CurPhase == 5)
	{
		if (PhaseTime >= 0.8f)
		{
			CurPhase++;
			PhaseTime = 0.0f;
		}
	}
	// 상단 1횡 6열로 이동
	else if (CurPhase == 6)
	{
		if (PhaseTime >= 2.0f)
		{
			CurPhase++;
			PhaseTime = 0.0f;
		}
	}
	// 하단 1횡 6열로 이동
	else if (CurPhase == 7)
	{
		if (PhaseTime >= 1.5f)
		{
			CurPhase = 1;
			PhaseTime = 0.0f;
		}
	}
	ChangeState(EControlState::SET);

}

void AArmosKngiht_Control::StartEnd()
{
	PlayerCharacter->ChangeState(EPlayerState::SwordGet);
	USoundManager::GetInstance().StopBGMSound();
	USoundManager::GetInstance().PlayEffectSound("BossClearFanfare.mp3");

	TimeEventer.PushEvent(11.0f, [this]()
		{
			PlayerCharacter->ChangeState(EPlayerState::Idle);
		});
}

void AArmosKngiht_Control::End(float DeltaTime)
{
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

void AArmosKngiht_Control::ChangeState(EControlState ControlState)
{
	switch (ControlState)
	{
	case EControlState::STAY:
		StartStay();
		break;
	case EControlState::SET:
		StartSet();
		break;
	case EControlState::MOVE:
		StartMove();
		break;
	case EControlState::END:
		StartEnd();
		break;
	default:
		break;
	}

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
	BossForces[BossForces.size() - 1] = ForstForce;
	MoveCallCount++;

	if (MoveCallCount == 6 && CurPhase == 2)
	{
		PhaseTime = 0.0f;
		CurPhase++;
		MoveCallCount = 0;
		ChangeState(EControlState::SET);
	}
	if (MoveCallCount == 2 && CurPhase == 4)
	{
		PhaseTime = 0.0f;
		CurPhase++;
		MoveCallCount = 0;
		ChangeState(EControlState::SET);
	}
}

FVector2D AArmosKngiht_Control::GetRotateLocation(FVector2D Location, float Degree)
{
	return FVector2D();
}

void AArmosKngiht_Control::DestoryArmosKnight(AArmosKnight* ArmosKnight)
{
	ArmosKnight->Destroy();
	BossEnemies.remove(ArmosKnight);

	if (BossEnemies.size() == 1)
	{
		std::list<AArmosKnight*>::iterator StartIter = BossEnemies.begin();
		std::list<AArmosKnight*>::iterator EndIter = BossEnemies.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AArmosKnight* CurArmosKnight = *StartIter;
			CurArmosKnight->ChangeState(EBossState::BERSERK_WAIT);
			CurArmosKnight->SetCurrentHP(50);
		}
	}
	else if (0 == BossEnemies.size())
	{
		TimeEventer.PushEvent(1.0f, [this]() {
				ChangeState(EControlState::END);
			});
	}
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
