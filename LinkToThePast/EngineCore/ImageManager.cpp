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
		MSGASSERT("���丮�� �ε��Ҽ� �����ϴ�." + std::string(Path));
		return;
	}

	if (EnginePath.IsExists() == false)
	{
		MSGASSERT("��ȿ���� ���� ���� ��� �Դϴ�." + std::string(Path));
		return;
	}

	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	std::string UpperName = UEngineString::ToUpper(KeyName);
	// ������ٰ� ���� �ƴմϴ�.
	UEngineWinImage* NewImage = new UEngineWinImage();
	NewImage->Load(WindowImage, Path);

	Images.insert({ UpperName , NewImage });

	UEngineSprite* NewSprite = new UEngineSprite();

	// �̹����� �ڸ��� ������ �Ǵ� ��ġ�� ���� ���� �������� �ڸ��� ���� �ϰڴ�.
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
		MSGASSERT("�������� ���� ��������Ʈ�� �ڸ����� �߽��ϴ�" + std::string(KeyName));
		return;
	}

	if (false == Images.contains(UpperName))
	{
		MSGASSERT("�������� ���� �̹����� ������� ��������Ʈ�� �ڸ����� �߽��ϴ�" + std::string(KeyName));
		return;
	}

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWinImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();

	if (0 != (Image->GetImageScale().iX() % CuttingSize.iX()))
	{
		MSGASSERT("��������Ʈ ���ÿ� x�� �� �������� �ʽ��ϴ�." + std::string(KeyName));
		return;
	}

	if (0 != (Image->GetImageScale().iY() % CuttingSize.iY()))
	{
		MSGASSERT("��������Ʈ ���ÿ� y�� �� �������� �ʽ��ϴ�." + std::string(KeyName));
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
	// ���� �̸� �Ǵ� ��θ� �빮�ڷ� ��ȯ
	std::string UpperName = UEngineString::ToUpper(KeyName);

	// ��
	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� ����Ϸ��� �߽��ϴ�" + std::string(KeyName));
		return nullptr;
	}

	//std::map<std::string, UEngineSprite*>::iterator FindIter = Sprites.find(UpperName);

	// �̰ɷ� 
	return Sprites[UpperName];
}