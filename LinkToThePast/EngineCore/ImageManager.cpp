#include "PreCompile.h"
#include "ImageManager.h"

#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineString.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineAPICore.h>

UImageManager::UImageManager()
{
}

UImageManager::~UImageManager()
{
	{
		std::map<std::string, UEngineWinImage*>::iterator StartIter = Images.begin();
		std::map<std::string, UEngineWinImage*>::iterator EndIter = Images.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			UEngineWinImage* CurRes = StartIter->second;
			if (nullptr != CurRes)
			{
				delete CurRes;
				CurRes = nullptr;
			}
		}
	}

	{
		std::map<std::string, UEngineSprite*>::iterator StartIter = Sprites.begin();
		std::map<std::string, UEngineSprite*>::iterator EndIter = Sprites.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			UEngineSprite* CurRes = StartIter->second;
			if (nullptr != CurRes)
			{
				delete CurRes;
				CurRes = nullptr;
			}
		}
	}
}

void UImageManager::Load(std::string_view Path)
{
	UEnginePath EnginePath = UEnginePath(Path);

	std::string FileName = EnginePath.GetFileName();

	Load(FileName, Path);
}

void UImageManager::Load(std::string_view KeyName, std::string_view Path)
{
	// 경로 저장
	UEnginePath EnginePath = UEnginePath(Path);

	// 경로가 유효한지 확인
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

	// 메인 윈도우 HDC를 사용하기 위한 윈도우 이미지 변수 생성
	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	// 파일 이름 통일을 위한 대문자화
	std::string UpperName = UEngineString::ToUpper(KeyName);

	if (Images.contains(UpperName) == true)
	{
		MSGASSERT("이미 로드된 이미지입니다. " + std::string(KeyName));
		return;
	}

	if (Sprites.contains(UpperName) == true)
	{
		MSGASSERT("이미 로드된 이미지입니다. " + std::string(KeyName));
		return;
	}

	// 만들었다고 끝이 아닙니다.
	UEngineWinImage* NewImage = new UEngineWinImage();
	NewImage->Load(WindowImage, Path);

	NewImage->SetName(UpperName);
	Images.insert({ UpperName , NewImage });

	UEngineSprite* NewSprite = new UEngineSprite();

	// 이미지를 자르는 기준이 되는 위치는 왼쪽 위를 기준으로 자르는 것을 하겠다.
	FTransform Trans;
	Trans.Location = { 0,0 };
	Trans.Scale = NewImage->GetImageScale();

	NewSprite->PushData(NewImage, Trans);
	NewSprite->SetName(UpperName);
	Sprites.insert({ UpperName , NewSprite });
}

void UImageManager::LoadFolder(std::string_view Path)
{
	// 함수 인자로 받은 경로를 가지고서 객체 생서
	UEnginePath EnginePath = UEnginePath(Path);

	std::string DirName = EnginePath.GetDirectoryName();

	LoadFolder(DirName, Path);
}

void UImageManager::LoadFolder(std::string_view KeyName, std::string_view Path)
{
	// 경로가 유효한지 검사
	UEnginePath EnginePath = UEnginePath(Path);

	if (EnginePath.IsExists() == false)
	{
		MSGASSERT("유효하지 않은 파일 경로입니다. " + std::string(Path));
		return;
	}

	std::string UpperName = UEngineString::ToUpper(KeyName);

	if (Sprites.contains(UpperName) == true)
	{
		MSGASSERT("이미 로드된 이미지입니다. " + UpperName);
		return;
	}

	// 새로운 스프라이트 객체 생성
	UEngineSprite* NewSprite = new UEngineSprite();

	// 스프라이트 목록에 추가
	Sprites.insert({ UpperName, NewSprite });

	// 이미지를 로드하기 위해서 필요한 Window  main HDC
	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	UEngineDirectory Dir = Path;
	// 모든 이미지 파일들들 저장
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		// 이미지 파일의 경로를 저장
		std::string FilePath = ImageFiles[i].GetPathToString();

		// 이미지 파일의 이름을 저장
		std::string UpperFileName = UEngineString::ToUpper(ImageFiles[i].GetFileName());

		// 윈도우 메인 HDC에 해당 이미지를 로드
		UEngineWinImage* NewImage = FindImage(UpperFileName);
		if (NewImage == nullptr)
		{
			NewImage = new UEngineWinImage();
			NewImage->SetName(UpperFileName);
			NewImage->Load(WindowImage, FilePath);
		}
		Images.insert({ UpperFileName, NewImage });

		FTransform Transform;
		Transform.Location = { 0, 0 };
		Transform.Scale = NewImage->GetImageScale();

		NewSprite->PushData(NewImage, Transform);


	}

}

void UImageManager::CuttingSprite(std::string_view _KeyName, int _X, int _Y)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 스프라이트를 자르려고 했습니다" + std::string(_KeyName));
		return;
	}

	if (false == Images.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 이미지를 기반으로 스프라이트를 자르려고 했습니다" + std::string(_KeyName));
		return;
	}

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWinImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();
	Sprite->SetName(UpperName);
	Image->SetName(UpperName);

	FVector2D Scale = Image->GetImageScale();

	Scale.X /= _X;
	Scale.Y /= _Y;

	CuttingSprite(_KeyName, Scale);
}

void UImageManager::CuttingSprite(std::string_view KeyName, FVector2D CuttingSize)
{
	std::string UpperName = UEngineString::ToUpper(KeyName);

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 스프라이트를 자르려고 했습니다. " + std::string(KeyName));
		return;
	}

	if (false == Images.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 이미지를 기반으로 스프라이트를 자르려고 했습니다. " + std::string(KeyName));
		return;
	}

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWinImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();
	Sprite->SetName(UpperName);
	Image->SetName(UpperName);

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
		MSGASSERT("로드하지 않은 스프라이트를 사용하려고 했습니다 " + std::string(KeyName));
		return nullptr;
	}

	//std::map<std::string, UEngineSprite*>::iterator FindIter = Sprites.find(UpperName);

	// 이걸로 
	return Sprites[UpperName];
}

UEngineWinImage* UImageManager::FindImage(std::string_view KeyName)
{
	std::string UpperName = UEngineString::ToUpper(KeyName);

	if (Images.contains(UpperName) == false)
	{
		MSGASSERT("로드하지 않은 스프라이트를 사용하려고 했습니다 " + std::string(KeyName));
		return nullptr;
	}

	return Images[UpperName];
}

void UImageManager::CreateCutSprite(std::string_view _SearchKeyName, std::string_view _NewSpriteKeyName, FVector2D _StartPos, FVector2D _CuttingSize, FVector2D _XYOffSet, UINT _Xcount, UINT _ImageCount)
{
	std::string SearchName = UEngineString::ToUpper(_SearchKeyName);
	std::string NewSpriteName = UEngineString::ToUpper(_NewSpriteKeyName);

	if (_Xcount <= 0)
	{
		MSGASSERT("이미지의 가로 갯수가 0 이하입니다.");
		return;
	}
	if (_ImageCount <= 0)
	{
		MSGASSERT("총 이미지 갯수가 0 이하입니다.");
		return;
	}
	if (Sprites.contains(SearchName) == false)
	{
		MSGASSERT(std::string(_SearchKeyName) + "라는 이름의 Sprite는 로드할 수 없습니다.");
		return;
	}
	if (Images.contains(SearchName) == false)
	{
		MSGASSERT(std::string(_SearchKeyName) + "라는 이름의 Sprite는 로드할 수 없습니다.");
		return;
	}
	if (Sprites.contains(NewSpriteName) == true)
	{
		MSGASSERT(std::string(_NewSpriteKeyName) + "라는 이름의 Sprite가 이미 존재합니다.");
		return;
	}
	if (Images.contains(NewSpriteName) == true)
	{
		MSGASSERT(std::string(_NewSpriteKeyName) + "라는 이름의 Image가 이미 존재합니다.");
		return;
	}


	UEngineSprite* Sprite = Sprites[SearchName];
	UEngineWinImage* Image = Images[SearchName];

	Sprite->ClearSpriteData();
	Sprite->SetName(SearchName);
	Image->SetName(SearchName);

	UINT YCount = _ImageCount / _Xcount;
	if (_ImageCount % _Xcount > 0)
		++YCount;

	float TotalSizeX = _StartPos.X + (_CuttingSize.X * _Xcount) + (_XYOffSet.X * (_Xcount - 1));
	float TotalSizeY = _StartPos.Y + (_CuttingSize.Y * YCount) + (_XYOffSet.Y * (YCount - 1));

	if (TotalSizeX > Image->GetImageScale().X)
	{
		MSGASSERT("필요한 이미지 가로 사이즈가 원본 이미지 사이즈보다 큽니다.");
		return;
	}
	if (TotalSizeY > Image->GetImageScale().Y)
	{
		MSGASSERT("필요한 이미지 세로 사이즈가 원본 이미지 사이즈보다 큽니다.");
		return;
	}

	FVector2D TotalSize = FVector2D(static_cast<int>(TotalSizeX), static_cast<int>(TotalSizeY));


	UEngineWinImage* NewImage = new UEngineWinImage();
	UEngineSprite* NewSprite = new UEngineSprite();
	NewImage->Create(UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage(), TotalSize);

	BitBlt(NewImage->GetDC(), 0, 0, static_cast<int>(TotalSizeX), static_cast<int>(TotalSizeY), Image->GetDC(), static_cast<int>(_StartPos.X), static_cast<int>(_StartPos.Y), SRCCOPY);

	Images.insert(make_pair(NewSpriteName, NewImage));
	Sprites.insert(make_pair(NewSpriteName, NewSprite));

	FVector2D CuttingPos = {};

	for (UINT y = 0; y < YCount; ++y)
	{
		CuttingPos.Y = _CuttingSize.Y * y + _XYOffSet.Y * y;

		for (UINT x = 0; x < _Xcount; ++x)
		{
			CuttingPos.X = _CuttingSize.X * x + _XYOffSet.X * x;
			FTransform insertInst = {};
			insertInst.Scale = _CuttingSize;
			insertInst.Location = CuttingPos;
			NewSprite->PushData(NewImage, insertInst);
		}
		CuttingPos.X = 0.f;
	}
}