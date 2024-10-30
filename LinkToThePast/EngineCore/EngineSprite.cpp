#include "PreCompile.h"
#include "EngineSprite.h"
#include <EngineBase/EngineDebug.h>

UEngineSprite::UEngineSprite()
{
}

UEngineSprite::~UEngineSprite()
{
}

void UEngineSprite::PushData(UEngineWinImage* Image, const FTransform& Trans)
{
	if (Trans.Scale.IsZeroed() == true)
	{
		MSGASSERT("ũ�Ⱑ 0�� �̹����� ����� �����ϴ�");
	}
	Data.push_back({ Image, Trans });
}

