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
	// TODO: Info 초기화
}

UEngineWinImage::~UEngineWinImage()
{
	if (nullptr != hBitMap)
	{
		DeleteObject(hBitMap);
		hBitMap = nullptr;
	}

	if (nullptr != ImageDC)
	{
		DeleteDC(ImageDC);
		ImageDC = nullptr;
	}
}

// 메인 윈도우 DC를 통해서 윈도우 창의 크기만큼 그려진 이미지를 초기화 될 때 호출
void UEngineWinImage::Create(UEngineWinImage* TargetImage, FVector2D Scale)
{
	// TargetImage가 nullptr이면 함수 종료
	if (TargetImage == nullptr)
	{
		MSGASSERT("Main windowDC를 넣지않고 이미지를 생성하려고 했습니다");
		return;
	}

	// TagetImage의 DC와 크기를 사용해 빈 이미지 데이터를 생성
	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(TargetImage->GetDC(), Scale.iX(), Scale.iY()));
	
	// 이미지를 수정할 수 있는 권한인 HDC를 새로 생성
	HDC NewImageDC = CreateCompatibleDC(TargetImage->GetDC());

	// HDC <=> HBITMAP 을 연결해야 이미지와 이미지를 수정하는 권한이 연결
	// 기본적으로 NewImageDC는 HBITMAP을 가지고 있으므로 전달받아서 삭제
	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	DeleteObject(OldBitMap);

	// 새로 만들어진 HBITMAP과 HDC를 멤버 변수에 할당
	hBitMap = NewBitmap;
	ImageDC = NewImageDC;
	
	//
	GetObject(hBitMap, sizeof(BITMAP), &Info);
}

// 백버퍼 이미지를 메인 윈도우 창 이미지에 옮길 떄 호출
void UEngineWinImage::CopyToBit(UEngineWinImage* TargetImage, const FTransform& Transform)
{
	// TargetImage, 즉 복사 받을 대상이 존재하지 않는다면 함수 종료
	if (TargetImage == nullptr)
	{
		MSGASSERT("복사받을 대상이 존재하지 않습니다.");
	}

	// 현재 이미지의 HDC 객체를 복사
	HDC CopyDC = ImageDC;
	// 복사받을 이미지의 HDC 객체를 복사
	HDC TargetDC = TargetImage->ImageDC;

	// 복사받을 이미지의 사각형의 크기를 확인
	FVector2D LeftTop = Transform.CenterLeftTop();
	FVector2D RightBot = Transform.CenterRightBottom();
	
	// 복사받을 이미지의 HDC를 사용하여 자신의 이미지를 그린다
	BitBlt(
		TargetDC,					// 복사받을 대상
		LeftTop.iX(),				// 그릴 시작 위치 X좌표
		LeftTop.iY(),				// 그릴 시작 위치 Y좌표
		Transform.Scale.iX(),		// 가로 크기
		Transform.Scale.iY(),		// 세로 크기
		CopyDC,						// 카피를 할 이미지
		0,							// 이미지 시작위치 X좌표
		0,							// 이미지 시작위치 Y좌표
		SRCCOPY);					// 카피 옵션
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

void UEngineWinImage::CopyToAlpha(UEngineWinImage* TargetImage, const FTransform& RenderTransform, const FTransform& LTImageTransform, unsigned char Alpha)
{
	BLENDFUNCTION BLEND;
	BLEND.BlendOp = AC_SRC_OVER;
	BLEND.BlendFlags = 0;
	BLEND.AlphaFormat = AC_SRC_ALPHA;
	BLEND.SourceConstantAlpha = Alpha;

	HDC CopyDC = ImageDC;
	HDC TargetDC = TargetImage->ImageDC;
	FVector2D LeftTop = RenderTransform.CenterLeftTop();

	AlphaBlend(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		RenderTransform.Scale.iX(),
		RenderTransform.Scale.iY(),
		CopyDC,
		LTImageTransform.Location.iX(),
		LTImageTransform.Location.iY(),
		LTImageTransform.Scale.iX(),
		LTImageTransform.Scale.iY(),
		BLEND
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
	else if (UpperExt == ".BMP")
	{
		HANDLE NewHandle = LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		NewBitmap = reinterpret_cast<HBITMAP>(NewHandle);
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

UColor UEngineWinImage::GetColor(FIntPoint _Point, UColor _DefaultColor = UColor::WHITE)
{
	if (0 > _Point.X)
	{
		return _DefaultColor;
	}
	if (0 > _Point.Y)
	{
		return _DefaultColor;
	}
	if (Info.bmWidth <= _Point.X)
	{
		return _DefaultColor;
	}
	if (Info.bmHeight <= _Point.Y)
	{
		return _DefaultColor;
	}
	// ::꼭 붙여야 한다. 명시적으로 전역에 존재하는 윈도우
	// UEngineWinImage::GetPixel 혼돈이 올수 있다.
	// RGBA
	// 1111
	UColor ResultColor = ::GetPixel(ImageDC, _Point.X, _Point.Y);
	return ResultColor;
}