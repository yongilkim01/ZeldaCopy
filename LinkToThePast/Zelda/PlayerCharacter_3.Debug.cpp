#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "BossGameMode.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>

void APlayerCharacter::PrintDebugInfo(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / DeltaTime));
	UEngineDebug::CoreOutPutString("Location : " + GetActorLocation().ToString(), GetDebugLocation(0));
	UEngineDebug::CoreOutPutString("Level : " + GetWorld()->GetName(), GetDebugLocation(1));
	//UEngineDebug::CoreOutPutString("PlayerScale : " + GetTransform().Scale.ToString());
	//UEngineDebug::CoreOutPutString("PlayerLefTop : " + GetTransform().CenterLeftTop().ToString());
	//UEngineDebug::CoreOutPutString("Player Room Name : " + CurRoom->GetName());
	//UEngineDebug::CoreOutPutString("Player Room Collision Name : " + this->CollisionImage->GetName());

			// 현재 플레이어의 위치
	FVector2D PlayerLocation = GetActorLocation() - GetCurRoom()->GetActorLocation();
	// 현재 플레이어의 위치에 있는 콜리전 색상
	UColor Color = GetCollisionImage()->GetColor(PlayerLocation);

	//UEngineDebug::CoreOutPutString("Current RGB : " + Color.ToString());
	UEngineDebug::CoreOutPutString("Room : " + GetCurRoom()->GetName(), GetDebugLocation(2));
	//UEngineDebug::CoreOutPutString("Current Room Collision Name : " + GetCollisionImage()->GetName(), GetNoneCameraLocation());

	UEngineDebug::CoreOutPutString("HP : " + std::to_string(this->CurrentHP), GetDebugLocation(3));
	//UEngineDebug::CoreOutPutString("Player order : " + std::to_string(this->SpriteRenderer->GetOrder()));
	//UEngineDebug::CoreOutPutString("KncokBack DeltaTime: " + std::to_string(KnockBackTime));

	if (true == HitCollision->IsActive())
	{
		UEngineDebug::CoreOutPutString("Collision : Alive", GetDebugLocation(4));
	}
	else
	{
		UEngineDebug::CoreOutPutString("Collision : Dead", GetDebugLocation(4));
	}

	switch (GetCurRoomFloor())
	{
	case ERoomFloor::FLOOR_1F:
		UEngineDebug::CoreOutPutString("Current floor : 1F", GetDebugLocation(5));
		break;
	case ERoomFloor::FLOOR_2F:
		UEngineDebug::CoreOutPutString("Current floor : 2F", GetDebugLocation(5));
		break;
	default:
		break;
	}

	switch (CurPlayerState)
	{
	case EPlayerState::Idle:
		UEngineDebug::CoreOutPutString("State : Idle ", GetDebugLocation(6));
		break;
	case EPlayerState::Move:
		UEngineDebug::CoreOutPutString("State : Move ", GetDebugLocation(6));
		break;
	case EPlayerState::Attack:
		UEngineDebug::CoreOutPutString("State : Attack ", GetDebugLocation(6));
		break;
	case EPlayerState::KnockBack:
		UEngineDebug::CoreOutPutString("State : KnockBack ", GetDebugLocation(6));
		break;
	case EPlayerState::Interact:
		UEngineDebug::CoreOutPutString("State : Interact ", GetDebugLocation(6));
		break;
	case EPlayerState::LiftMove:
		UEngineDebug::CoreOutPutString("State : LiftMove ", GetDebugLocation(6));
		break;
	case EPlayerState::LiftIdle:
		UEngineDebug::CoreOutPutString("State : LiftIdle ", GetDebugLocation(6));
		break;
	default:
		break;
	}

	if (UEngineInput::GetInst().IsPress('U') == true)
	{
		DebugSwitch();
		UEngineDebug::SwitchIsDebug();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F2))
	{
		UEngineDebug::SwitchIsDebug();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F3))
	{
		// static썼다. 
		UEngineAPICore::GetCore()->ResetLevel<ABossGameMode, APlayerCharacter>("Boss");
		UEngineAPICore::GetCore()->OpenLevel("Boss");
	}
}