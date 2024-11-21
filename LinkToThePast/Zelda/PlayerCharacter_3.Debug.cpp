#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "BossGameMode.h"
#include "ContentsEnum.h"
#include "PlayerDataManager.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>

void APlayerCharacter::PrintDebugInfo(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / DeltaTime));

	FVector2D PlayerLocation = GetActorLocation() - GetCurRoom()->GetActorLocation();
	// 현재 플레이어의 위치에 있는 콜리전 색상
	UColor Color = GetCollisionImage()->GetColor(PlayerLocation);

	UEngineDebug::CoreOutPutString("Current RGB : " + Color.ToString());

	UEngineDebug::CoreOutPutString("Location : " + GetActorLocation().ToString(), GetDebugLocation(0));
	UEngineDebug::CoreOutPutString("Level : " + GetWorld()->GetName(), GetDebugLocation(1));
	UEngineDebug::CoreOutPutString("Room : " + GetCurRoom()->GetName(), GetDebugLocation(2));
	UEngineDebug::CoreOutPutString("Collision : " + GetCollisionImage()->GetName(), GetDebugLocation(3));
	UEngineDebug::CoreOutPutString("HP : " + std::to_string(PlayerDataManager::GetInstance().GetHP()), GetDebugLocation(4));

	if (true == HitCollision->IsActive())
	{
		UEngineDebug::CoreOutPutString("Collision : Alive", GetDebugLocation(5));
	}
	else
	{
		UEngineDebug::CoreOutPutString("Collision : Dead", GetDebugLocation(5));
	}

	switch (GetCurRoomFloor())
	{
	case ERoomFloor::FLOOR_1F:
		UEngineDebug::CoreOutPutString("Current floor : 1F", GetDebugLocation(6));
		break;
	case ERoomFloor::FLOOR_2F:
		UEngineDebug::CoreOutPutString("Current floor : 2F", GetDebugLocation(6));
		break;
	default:
		break;
	}

	switch (CurPlayerState)
	{
	case EPlayerState::Idle:
		UEngineDebug::CoreOutPutString("State : Idle ", GetDebugLocation(7));
		break;
	case EPlayerState::Move:
		UEngineDebug::CoreOutPutString("State : Move ", GetDebugLocation(7));
		break;
	case EPlayerState::Attack:
		UEngineDebug::CoreOutPutString("State : Attack ", GetDebugLocation(7));
		break;
	case EPlayerState::KnockBack:
		UEngineDebug::CoreOutPutString("State : KnockBack ", GetDebugLocation(7));
		break;
	case EPlayerState::Interact:
		UEngineDebug::CoreOutPutString("State : Interact ", GetDebugLocation(7));
		break;
	case EPlayerState::LiftMove:
		UEngineDebug::CoreOutPutString("State : LiftMove ", GetDebugLocation(7));
		break;
	case EPlayerState::LiftIdle:
		UEngineDebug::CoreOutPutString("State : LiftIdle ", GetDebugLocation(7));
		break;
	default:
		break;
	}

	if (true == UEngineInput::GetInst().IsDown('1'))
	{
		DebugSwitch();
	}
	if (true == UEngineInput::GetInst().IsDown('2'))
	{
		UEngineDebug::SwitchIsDebug();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F3))
	{
		// static썼다. 
		UEngineAPICore::GetCore()->ResetLevel<ABossGameMode, APlayerCharacter>("Boss");
		UEngineAPICore::GetCore()->OpenLevel("Boss");
	}
	if (UEngineInput::GetInst().IsPress(VK_NUMPAD8) == true)
	{
		PlayerDataManager::GetInstance().AddMagicGaguge(1);
	}
	if (UEngineInput::GetInst().IsPress(VK_NUMPAD2) == true)
	{
		PlayerDataManager::GetInstance().AddMagicGaguge(-1);
	}

	if (UEngineInput::GetInst().IsDown(VK_NUMPAD6) == true)
	{
		PlayerDataManager::GetInstance().AddHP(1);
	}
	if (UEngineInput::GetInst().IsDown(VK_NUMPAD4) == true)
	{
		PlayerDataManager::GetInstance().AddHP(-1);
	}
}