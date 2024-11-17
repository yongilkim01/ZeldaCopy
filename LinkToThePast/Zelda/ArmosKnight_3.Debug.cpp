#include "PreCompile.h"
#include "ArmosKnight.h"
#include "PlayerCharacter.h"

#include <EngineCore/EngineCoreDebug.h>

void AArmosKnight::PrintDebugInfo()
{
	UEngineDebug::CoreOutPutString("///////////////////////// Armos knight Debug /////////////////////////");
	UEngineDebug::CoreOutPutString("Kncok back count : " + std::to_string(KnockBackCount));
	UEngineDebug::CoreOutPutString("Current hp : " + std::to_string(CurrentHP));

	if (TargetCharacter != nullptr)
	{
		UEngineDebug::CoreOutPutString("Target location : " + TargetCharacter->GetActorLocation().ToString());
	}
	switch (CurBossState)
	{
	case EBossState::NONE:
		UEngineDebug::CoreOutPutString("Armos knight state : NONE");
		break;
	case EBossState::MOVE:
		UEngineDebug::CoreOutPutString("Armos knight state : MOVE");
		break;
	case EBossState::KNOCKBACK:
		UEngineDebug::CoreOutPutString("Armos knight state : KNOCKBACK");
		break;
	default:
		break;
	}
}