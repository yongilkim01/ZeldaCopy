#pragma once
/** OS Header */
#include <Windows.h>

/** Engine Base Header */
#include <EngineBase/EngineMath.h>
#include <EngineBase/Object.h>

/**
*  ������ API�� ����� �̹����� ������ Ŭ����
*  �̹����� �ϳ��� HDC�� ����
*  �̹��� == HDC
*/
class UEngineWinImage : public UObject
{
public:
	/** ������ �Ҹ��� */
	UEngineWinImage();
	~UEngineWinImage();

	/** ��ü ���� ���� */
	UEngineWinImage(const UEngineWinImage& Other) = delete;
	UEngineWinImage(UEngineWinImage&& Other) noexcept = delete;
	UEngineWinImage& operator=(const UEngineWinImage& Other) = delete;
	UEngineWinImage& operator=(UEngineWinImage&& Other) noexcept = delete;

	/** �ٸ� EngineWinImage ��ü�� ������ ���� ���� */
	void Create(UEngineWinImage* TargetImage, FVector2D Scale);
	void CopyToBit(UEngineWinImage* TargetImage, const FTransform& Trans);
	void CopyToTrans(UEngineWinImage* TargetImage
		, const FTransform& RenderTrans
		, const FTransform& LTImageTrans
		, UColor Color = UColor(255, 0, 255, 0));
	
	void CopyToAlpha(UEngineWinImage* TargetImage
		, const FTransform& RenderTransform
		, const FTransform& LTImageTransform 
		, unsigned char Alpha);

	void Load(UEngineWinImage* TargetImage, std::string_view Path);

	void Create(HDC DC) { ImageDC = DC; }
	FVector2D GetImageScale() const { return { Info.bmWidth, Info.bmHeight }; }
	HDC GetDC() { return ImageDC; }
	UColor GetColor(FIntPoint Point, UColor DefaultColor);
	UColor GetColor(FVector2D Point, UColor DefaultColor = UColor::WHITE)
	{
		return GetColor(Point.ConvertToPoint(), DefaultColor);
	}

protected:

private:
	HDC ImageDC = nullptr;
	HBITMAP hBitMap = nullptr;

	BITMAP Info;
};

