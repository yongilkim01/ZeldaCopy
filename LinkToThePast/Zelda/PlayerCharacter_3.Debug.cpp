#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>

void APlayerCharacter::PrintDebugInfo(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());
	UEngineDebug::CoreOutPutString("PlayerScale : " + GetTransform().Scale.ToString());
	UEngineDebug::CoreOutPutString("PlayerLefTop : " + GetTransform().CenterLeftTop().ToString());
	UEngineDebug::CoreOutPutString("Player Room Name : " + CurRoom->GetName());
	UEngineDebug::CoreOutPutString("Player Room Collision Name : " + this->CollisionImage->GetName());

	UEngineDebug::CoreOutPutString("Player HP : " + std::to_string(this->CurrentHP));
	UEngineDebug::CoreOutPutString("KncokBack DeltaTime: " + std::to_string(KnockBackTime));


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
	default:
		break;
	}

	if (UEngineInput::GetInst().IsPress('U') == true)
	{
		if (IsDebug() == true) DebugOff();
		else if (IsDebug() == false) DebugOn();
	}
}