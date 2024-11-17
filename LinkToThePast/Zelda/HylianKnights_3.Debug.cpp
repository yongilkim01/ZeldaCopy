#include "PreCompile.h"
#include "HylianKnights.h"
#include "Room.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>

void AHylianKnight::PrintDebugInfo()
{
	UEngineDebug::CoreOutPutString("//////////////////////////// Enemy Debug ////////////////////////////");
	UEngineDebug::CoreOutPutString("Enemy location : " + GetActorLocation().ToString());
	UEngineDebug::CoreOutPutString("Enemy hp : " + std::to_string(this->CurrentHP));
	UEngineDebug::CoreOutPutString("Enemy cool time : " + std::to_string(this->AttackCoolTime));

	UEngineDebug::CoreOutPutString("Enemy order : " + std::to_string(this->SpriteRenderer->GetOrder()));

	if (GetCurRoom() != nullptr)
	{
		UEngineDebug::CoreOutPutString("Cur room : " + GetCurRoom()->GetName());
	}

	switch (CurEnemyState)
	{
	case EEnemyState::Patrol:
		UEngineDebug::CoreOutPutString("Enemy Current State : Patrol ");
		break;
	case EEnemyState::Trace:
		UEngineDebug::CoreOutPutString("Enemy Current State : Trace ");
		break;
	case EEnemyState::Attack:
		UEngineDebug::CoreOutPutString("Enemy Current State : Attack ");
		break;
	case EEnemyState::KnockBack:
		UEngineDebug::CoreOutPutString("Enemy Current State : KnockBack ");
		break;
	default:
		break;
	}
}
