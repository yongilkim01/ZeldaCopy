#include "PreCompile.h"
#include "EngineWinImage.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>

// GDI Plus 용 헤더
#include <objidl.h>
#include <gdiplus.h>

// BMP 확장용 라이브러리
#pragma comment(lib, "Msimg32.lib")
// PNG를 통한 window 네이티브 그래픽 확장용 라이브러리
#pragma comment(lib, "Gdiplus.lib")

UEngineWinImage::UEngineWinImage()
{
}

UEngineWinImage::~UEngineWinImage()
{
}

void UEngineWinImage::Create(UEngineWinImage* _TargetImage, FVector2D _Scale)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("Main windowDC를 넣지않고 이미지를 생성하려고 했습니다");
		return;
	}

	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(_TargetImage->GetDC(), _Scale.iX(), _Scale.iY()));
	
	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());

	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	DeleteObject(OldBitMap);

	hBitMap = NewBitmap;
	ImageDC = NewImageDC;
	
	GetObject(hBitMap, sizeof(BITMAP), &Info);
}

void UEngineWinImage::CopyToBit(UEngineWinImage* _TargetImage, const FTransform& _Trans)
{
	if (_TargetImage == nullptr)
	{
		MSGASSERT("복사받을 대상이 존재하지 않습니다.");
	}

	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;

	FVector2D LeftTop = _Trans.CenterLeftTop();
	FVector2D RightBot = _Trans.CenterRightBottom();

	BitBlt(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_Trans.Scale.iX(),
		_Trans.Scale.iY(),
		CopyDC,
		0,
		0,
		SRCCOPY);
}

void UEngineWinImage::CopyToTrans(UEngineWinImage* _TargetImage, const FTransform& _RenderTrans, const FTransform& _LTImageTrans, UColor _Color)
{
	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;

	FVector2D LeftTop = _RenderTrans.CenterLeftTop();

	TransparentBlt(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_RenderTrans.Scale.iX(),
		_RenderTrans.Scale.iY(),
		CopyDC,
		_LTImageTrans.Location.iX(),
		_LTImageTrans.Location.iY(),
		_LTImageTrans.Scale.iX(),
		_LTImageTrans.Scale.iY(),
		_Color.Color
	);
}

void UEngineWinImage::Load(UEngineWinImage* _TargetImage, std::string_view _Path)
{
	UEnginePath Path = _Path;

	// 확장자를 대문자로 치환
	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	HBITMAP NewBitmap = nullptr;

	if (UpperExt == ".PNG")
	{
		ULONG_PTR GidPlusToken = 0;

		Gdiplus::GdiplusStartupInput StartupInput;
		Gdiplus::GdiplusStartup(&GidPlusToken, &StartupInput, nullptr);

		// 경로를 wchar로 변환
		std::wstring WidePath = UEngineString::AnsiToUnicode(_Path);

		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(WidePath.c_str());

		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status Stat = pBitMap->GetHBITMAP(Gdiplus::Color(255, 255, 0, 255), &NewBitmap);
	
		if (Gdiplus::Status::Ok != Stat)
		{
			MSGASSERT("Png 이미지 로드에 실패했습니다." + std::string(_Path));
			return;
		}

		delete pBitMap;
		delete pImage;
	
	}

	if (NewBitmap == nullptr)
	{
		MSGASSERT("이미지 로딩에 실패했습니다");
		return;
	}

	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());

	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	DeleteObject(OldBitMap);

	hBitMap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitMap, sizeof(BITMAP), &Info);

}
