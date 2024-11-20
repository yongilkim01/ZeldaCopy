#include "PreCompile.h"
#include "EnemyKnight.h"
#include "Room.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>

void AEnemyKnight::PrintDebugInfo()
{
	UEngineDebug::CoreOutPutString("Location : " + GetActorLocation().ToString(), GetDebugLocation(0));
	UEngineDebug::CoreOutPutString("Level : " + GetWorld()->GetName(), GetDebugLocation(1));
	UEngineDebug::CoreOutPutString("Room : " + GetCurRoom()->GetName(), GetDebugLocation(2));
	UEngineDebug::CoreOutPutString("HP : " + std::to_string(this->CurrentHP), GetDebugLocation(3));

	switch (GetCurRoomFloor())
	{
	case ERoomFloor::FLOOR_1F:
		UEngineDebug::CoreOutPutString("Floor : 1F", GetDebugLocation(4));
		break;
	case ERoomFloor::FLOOR_2F:
		UEngineDebug::CoreOutPutString("Floor : 2F", GetDebugLocation(4));
		break;
	default:
		break;
	}

	switch (CurEnemyState)
	{
	case EEnemyState::Patrol:
		UEngineDebug::CoreOutPutString("State : Patrol", GetDebugLocation(5));
		break;
	case EEnemyState::Trace:
		UEngineDebug::CoreOutPutString("State : Trace", GetDebugLocation(5));
		break;
	case EEnemyState::Attack:
		UEngineDebug::CoreOutPutString("State : Attack", GetDebugLocation(5));
		break;
	case EEnemyState::KnockBack:
		UEngineDebug::CoreOutPutString("State : KnockBack", GetDebugLocation(5));
		break;
	default:
		break;
	}
}
