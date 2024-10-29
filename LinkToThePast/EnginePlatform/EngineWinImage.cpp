#include "PreCompile.h"
#include "EngineWinImage.h"
#include <EngineBase/EngineDebug.h>

UEngineWinImage::UEngineWinImage()
{
}

UEngineWinImage::~UEngineWinImage()
{
}

void UEngineWinImage::Create(FVector2D _Scale)
{
	HBITMAP NewBitMap = static_cast<HBITMAP>(CreateCompatibleBitmap(nullptr, _Scale.iX(), _Scale.iY()));
	
	HDC NewImageDC = CreateCompatibleDC(nullptr);

	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitMap));
	DeleteObject(OldBitMap);

	hBitMap = NewBitMap;
	ImageDC = NewImageDC;
}