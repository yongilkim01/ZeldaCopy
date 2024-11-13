#include "PreCompile.h"
#include "EngineWinImage.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>

// GDI Plus �� ���
#include <objidl.h>
#include <gdiplus.h>

// BMP Ȯ��� ���̺귯��
#pragma comment(lib, "Msimg32.lib")
// PNG�� ���� window ����Ƽ�� �׷��� Ȯ��� ���̺귯��
#pragma comment(lib, "Gdiplus.lib")


UEngineWinImage::UEngineWinImage()
{
	// TODO: Info �ʱ�ȭ
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

// ���� ������ DC�� ���ؼ� ������ â�� ũ�⸸ŭ �׷��� �̹����� �ʱ�ȭ �� �� ȣ��
void UEngineWinImage::Create(UEngineWinImage* TargetImage, FVector2D Scale)
{
	// TargetImage�� nullptr�̸� �Լ� ����
	if (TargetImage == nullptr)
	{
		MSGASSERT("Main windowDC�� �����ʰ� �̹����� �����Ϸ��� �߽��ϴ�");
		return;
	}

	// TagetImage�� DC�� ũ�⸦ ����� �� �̹��� �����͸� ����
	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(TargetImage->GetDC(), Scale.iX(), Scale.iY()));
	
	// �̹����� ������ �� �ִ� ������ HDC�� ���� ����
	HDC NewImageDC = CreateCompatibleDC(TargetImage->GetDC());

	// HDC <=> HBITMAP �� �����ؾ� �̹����� �̹����� �����ϴ� ������ ����
	// �⺻������ NewImageDC�� HBITMAP�� ������ �����Ƿ� ���޹޾Ƽ� ����
	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	DeleteObject(OldBitMap);

	// ���� ������� HBITMAP�� HDC�� ��� ������ �Ҵ�
	hBitMap = NewBitmap;
	ImageDC = NewImageDC;
	
	//
	GetObject(hBitMap, sizeof(BITMAP), &Info);
}

// ����� �̹����� ���� ������ â �̹����� �ű� �� ȣ��
void UEngineWinImage::CopyToBit(UEngineWinImage* TargetImage, const FTransform& Transform)
{
	// TargetImage, �� ���� ���� ����� �������� �ʴ´ٸ� �Լ� ����
	if (TargetImage == nullptr)
	{
		MSGASSERT("������� ����� �������� �ʽ��ϴ�.");
	}

	// ���� �̹����� HDC ��ü�� ����
	HDC CopyDC = ImageDC;
	// ������� �̹����� HDC ��ü�� ����
	HDC TargetDC = TargetImage->ImageDC;

	// ������� �̹����� �簢���� ũ�⸦ Ȯ��
	FVector2D LeftTop = Transform.CenterLeftTop();
	FVector2D RightBot = Transform.CenterRightBottom();
	
	// ������� �̹����� HDC�� ����Ͽ� �ڽ��� �̹����� �׸���
	BitBlt(
		TargetDC,					// ������� ���
		LeftTop.iX(),				// �׸� ���� ��ġ X��ǥ
		LeftTop.iY(),				// �׸� ���� ��ġ Y��ǥ
		Transform.Scale.iX(),		// ���� ũ��
		Transform.Scale.iY(),		// ���� ũ��
		CopyDC,						// ī�Ǹ� �� �̹���
		0,							// �̹��� ������ġ X��ǥ
		0,							// �̹��� ������ġ Y��ǥ
		SRCCOPY);					// ī�� �ɼ�
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

	// Ȯ���ڸ� �빮�ڷ� ġȯ
	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	HBITMAP NewBitmap = nullptr;

	if (UpperExt == ".PNG")
	{
		ULONG_PTR GidPlusToken = 0;

		Gdiplus::GdiplusStartupInput StartupInput;
		Gdiplus::GdiplusStartup(&GidPlusToken, &StartupInput, nullptr);

		// ��θ� wchar�� ��ȯ
		std::wstring WidePath = UEngineString::AnsiToUnicode(_Path);

		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(WidePath.c_str());

		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status Stat = pBitMap->GetHBITMAP(Gdiplus::Color(255, 255, 0, 255), &NewBitmap);
	
		if (Gdiplus::Status::Ok != Stat)
		{
			MSGASSERT("Png �̹��� �ε忡 �����߽��ϴ�." + std::string(_Path));
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
		MSGASSERT("�̹��� �ε��� �����߽��ϴ�");
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
	// ::�� �ٿ��� �Ѵ�. ��������� ������ �����ϴ� ������
	// UEngineWinImage::GetPixel ȥ���� �ü� �ִ�.
	// RGBA
	// 1111
	UColor ResultColor = ::GetPixel(ImageDC, _Point.X, _Point.Y);
	return ResultColor;
}