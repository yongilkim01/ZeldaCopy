#pragma once
/** Engine Header */
#include <EnginePlatform/EngineWinImage.h>
#include <EngineBase/EngineDebug.h>

/** Std Header */
#include <vector>

// ���� :
class UEngineSprite : public UObject
{
public:
	class USpriteData
	{
	public:
		UEngineWinImage* Image;

		/** �̹����� ���� ���� Ʈ������ */
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
			MSGASSERT("��������Ʈ�� �ε����� �����Ͽ� ����Ϸ��� �߽��ϴ�. " + GetName());
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

