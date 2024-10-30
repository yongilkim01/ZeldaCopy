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
		MSGASSERT("크기가 0인 이미지를 만들수 없습니다");
	}
	Data.push_back({ Image, Trans });
}

