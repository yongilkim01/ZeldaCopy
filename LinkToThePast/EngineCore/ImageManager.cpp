#include "PreCompile.h"
#include "ImageManager.h"

#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/EngineAPICore.h>

UImageManager::UImageManager()
{
}

UImageManager::~UImageManager()
{
}

void UImageManager::Load(std::string_view Path)
{
	UEnginePath EnginePath = UEnginePath(Path);

	std::string FileName = EnginePath.GetFileName();

	Load(FileName, Path);
}

void UImageManager::Load(std::string_view KeyName, std::string_view Path)
{
	UEnginePath EnginePath = UEnginePath(Path);

	if (EnginePath.IsDirectory() == true)
	{
		MSGASSERT("디렉토리는 로드할수 없습니다." + std::string(Path));
		return;
	}

	if (EnginePath.IsExists() == false)
	{
		MSGASSERT("유효하지 않은 파일 경로 입니다." + std::string(Path));
		return;
	}

	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	std::string UpperName = UEngineString::ToUpper(KeyName);
	// 만들었다고 끝이 아닙니다.
	UEngineWinImage* NewImage = new UEngineWinImage();
	NewImage->Load(WindowImage, Path);

	Images.insert({ UpperName , NewImage });

	UEngineSprite* NewSprite = new UEngineSprite();

	// 이미지를 자르는 기준이 되는 위치는 왼쪽 위를 기준으로 자르는 것을 하겠다.
	FTransform Trans;
	Trans.Location = { 0,0 };
	Trans.Scale = NewImage->GetImageScale();

	NewSprite->PushData(NewImage, Trans);

	Sprites.insert({ UpperName , NewSprite });
}

void UImageManager::CuttingSprite(std::string_view KeyName, FVector2D CuttingSize)
{
	std::string UpperName = UEngineString::ToUpper(KeyName);

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 스프라이트를 자르려고 했습니다" + std::string(KeyName));
		return;
	}

	if (false == Images.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 이미지를 기반으로 스프라이트를 자르려고 했습니다" + std::string(KeyName));
		return;
	}

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWinImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();

	if (0 != (Image->GetImageScale().iX() % CuttingSize.iX()))
	{
		MSGASSERT("스프라이트 컷팅에 x가 딱 떨어지지 않습니다." + std::string(KeyName));
		return;
	}

	if (0 != (Image->GetImageScale().iY() % CuttingSize.iY()))
	{
		MSGASSERT("스프라이트 컷팅에 y가 딱 떨어지지 않습니다." + std::string(KeyName));
		return;
	}

	int SpriteX = Image->GetImageScale().iX() / CuttingSize.iX();
	int SpriteY = Image->GetImageScale().iY() / CuttingSize.iY();

	FTransform CuttingTrans;

	CuttingTrans.Location = FVector2D::ZERO;
	CuttingTrans.Scale = CuttingSize;

	for (size_t y = 0; y < SpriteY; ++y)
	{
		for (size_t x = 0; x < SpriteX; ++x)
		{
			Sprite->PushData(Image, CuttingTrans);
			CuttingTrans.Location.X += CuttingSize.X;
		}

		CuttingTrans.Location.X = 0.0f;
		CuttingTrans.Location.Y += CuttingSize.Y;
	}
}

bool UImageManager::IsLoadSprite(std::string_view KeyName)
{
	std::string UpperName = UEngineString::ToUpper(KeyName);

	return Sprites.contains(UpperName);
}

UEngineSprite* UImageManager::FindSprite(std::string_view KeyName)
{
	// 파일 이름 또는 경로를 대문자로 변환
	std::string UpperName = UEngineString::ToUpper(KeyName);

	// 포
	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("로드하지 않은 스프라이트를 사용하려고 했습니다" + std::string(KeyName));
		return nullptr;
	}

	//std::map<std::string, UEngineSprite*>::iterator FindIter = Sprites.find(UpperName);

	// 이걸로 
	return Sprites[UpperName];
}