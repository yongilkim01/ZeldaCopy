#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "BossGameMode.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

void APlayerCharacter::PrintDebugInfo(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / DeltaTime));
	UEngineDebug::CoreOutPutString("//////////////////////////// Player Debug ////////////////////////////");
	UEngineDebug::CoreOutPutString("Player location : " + GetActorLocation().ToString());
	//UEngineDebug::CoreOutPutString("PlayerScale : " + GetTransform().Scale.ToString());
	//UEngineDebug::CoreOutPutString("PlayerLefTop : " + GetTransform().CenterLeftTop().ToString());
	//UEngineDebug::CoreOutPutString("Player Room Name : " + CurRoom->GetName());
	//UEngineDebug::CoreOutPutString("Player Room Collision Name : " + this->CollisionImage->GetName());

	UEngineDebug::CoreOutPutString("Player hp : " + std::to_string(this->CurrentHP));
	UEngineDebug::CoreOutPutString("Player order : " + std::to_string(this->SpriteRenderer->GetOrder()));
	if (GetCurRoom() != nullptr)
	{
		UEngineDebug::CoreOutPutString("Cur room : " + GetCurRoom()->GetName());
	}

	//UEngineDebug::CoreOutPutString("KncokBack DeltaTime: " + std::to_string(KnockBackTime));

	if (true == HitCollision->IsActive())
	{
		UEngineDebug::CoreOutPutString("Player body collision still alive");
	}
	else
	{
		UEngineDebug::CoreOutPutString("Player body collision dead");
	}


	switch (CurPlayerState)
	{
	case EPlayerState::Idle:
		UEngineDebug::CoreOutPutString("Player Current State : Idle ");
		break;
	case EPlayerState::Move:
		UEngineDebug::CoreOutPutString("Player Current State : Move ");
		break;
	case EPlayerState::Attack:
		UEngineDebug::CoreOutPutString("Player Current State : Attack ");
		break;
	case EPlayerState::KnockBack:
		UEngineDebug::CoreOutPutString("Player Current State : KnockBack ");
		break;
	default:
		break;
	}

	if (UEngineInput::GetInst().IsPress('U') == true)
	{
		if (IsDebug() == true) DebugOff();
		else if (IsDebug() == false) DebugOn();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F2))
	{
		UEngineDebug::SwitchIsDebug();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F3))
	{
		// static½è´Ù. 
		UEngineAPICore::GetCore()->ResetLevel<ABossGameMode, APlayerCharacter>("Boss2");
		UEngineAPICore::GetCore()->OpenLevel("Boss2");
	}
}