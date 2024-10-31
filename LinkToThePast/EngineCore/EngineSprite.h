#pragma once
/** Engine Header */
#include <EnginePlatform/EngineWinImage.h>
#include <EngineBase/EngineDebug.h>

/** Std Header */
#include <vector>

// 설명 :
class UEngineSprite : public UObject
{
public:
	class USpriteData
	{
	public:
		UEngineWinImage* Image;

		/** 이미지의 영역 지정 트랜스폼 */
		FTransform Transform;
	};

	// constrcuter destructer
	UEngineSprite();
	~UEngineSprite();

	// delete Function
	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	void PushData(UEngineWinImage* Image, const FTransform& Trans);

	USpriteData GetSpriteData(int Index = 0)
	{
		if (Index >= Data.size())
		{
			MSGASSERT("스프라이트의 인덱스를 오버하여 사용하려고 했습니다. " + GetName());
		}
		return Data[Index];
	}

	void ClearSpriteData()
	{
		Data.clear();
	}

protected:
	std::vector<USpriteData> Data;

private:

};

