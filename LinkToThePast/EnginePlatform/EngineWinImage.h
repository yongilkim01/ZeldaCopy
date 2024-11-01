#pragma once
/** OS Header */
#include <Windows.h>

/** Engine Base Header */
#include <EngineBase/EngineMath.h>
#include <EngineBase/Object.h>

/**
*  윈도우 API를 사용한 이미지를 래핑한 클래스
*  이미지는 하나의 HDC를 보유
*  이미지 == HDC
*/
class UEngineWinImage : public UObject
{
public:
	/** 생성자 소멸자 */
	UEngineWinImage();
	~UEngineWinImage();

	/** 객체 복사 방지 */
	UEngineWinImage(const UEngineWinImage& Other) = delete;
	UEngineWinImage(UEngineWinImage&& Other) noexcept = delete;
	UEngineWinImage& operator=(const UEngineWinImage& Other) = delete;
	UEngineWinImage& operator=(UEngineWinImage&& Other) noexcept = delete;

	/** 다른 EngineWinImage 객체의 정보를 토대로 생성 */
	void Create(UEngineWinImage* TargetImage, FVector2D Scale);
	void CopyToBit(UEngineWinImage* TargetImage, const FTransform& Trans);
	void CopyToTrans(UEngineWinImage* TargetImage
		, const FTransform& RenderTrans
		, const FTransform& LTImageTrans
		, UColor Color = UColor(255, 0, 255, 0));
	void Load(UEngineWinImage* TargetImage, std::string_view Path);

	inline void Create(HDC DC) { ImageDC = DC; }
	inline FVector2D GetImageScale() const { return { Info.bmWidth, Info.bmHeight }; }
	inline HDC GetDC() { return ImageDC; }

protected:

private:
	HDC ImageDC = nullptr;
	HBITMAP hBitMap = nullptr;

	BITMAP Info;
};

