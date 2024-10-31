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
}

void UImageManager::Load(std::string_view Path)
{
	UEnginePath EnginePath = UEnginePath(Path);

	std::string FileName = EnginePath.GetFileName();

	Load(FileName, Path);
}

void UImageManager::Load(std::string_view KeyName, std::string_view Path)
{
	// ��� ����
	UEnginePath EnginePath = UEnginePath(Path);

	// ��ΰ� ��ȿ���� Ȯ��
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

	// ���� ������ HDC�� ����ϱ� ���� ������ �̹��� ���� ����
	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	// ���� �̸� ������ ���� �빮��ȭ
	std::string UpperName = UEngineString::ToUpper(KeyName);

	if (Images.contains(UpperName) == true)
	{
		MSGASSERT("�̹� �ε�� �̹����Դϴ�. " + std::string(KeyName));
		return;
	}

	if (Sprites.contains(UpperName) == true)
	{
		MSGASSERT("�̹� �ε�� �̹����Դϴ�. " + std::string(KeyName));
		return;
	}

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

void UImageManager::LoadFolder(std::string_view Path)
{
	// �Լ� ���ڷ� ���� ��θ� ������ ��ü ����
	UEnginePath EnginePath = UEnginePath(Path);

	std::string DirName = EnginePath.GetDirectoryName();

	LoadFolder(DirName, Path);
}

void UImageManager::LoadFolder(std::string_view KeyName, std::string_view Path)
{
	// ��ΰ� ��ȿ���� �˻�
	UEnginePath EnginePath = UEnginePath(Path);

	if (EnginePath.IsExists() == false)
	{
		MSGASSERT("��ȿ���� ���� ���� ����Դϴ�. " + std::string(Path));
		return;
	}

	std::string UpperName = UEngineString::ToUpper(KeyName);

	if (Sprites.contains(UpperName) == true)
	{
		MSGASSERT("�̹� �ε�� �̹����Դϴ�. " + UpperName);
		return;
	}

	// ���ο� ��������Ʈ ��ü ����
	UEngineSprite* NewSprite = new UEngineSprite();

	// ��������Ʈ ��Ͽ� �߰�
	Sprites.insert({ UpperName, NewSprite });

	// �̹����� �ε��ϱ� ���ؼ� �ʿ��� Window  main HDC
	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	UEngineDirectory Dir = Path;
	// ��� �̹��� ���ϵ�� ����
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		// �̹��� ������ ��θ� ����
		std::string FilePath = ImageFiles[i].GetPathToString();

		// �̹��� ������ �̸��� ����
		std::string FileName = UEngineString::ToUpper(ImageFiles[i].GetFileName());

		// ������ ���� HDC�� �ش� �̹����� �ε�
		UEngineWinImage* NewImage = new UEngineWinImage();
		NewImage->Load(WindowImage, FilePath);
		Images.insert({ FileName, NewImage });

		FTransform Transform;
		Transform.Location = { 0, 0 };
		Transform.Scale = NewImage->GetImageScale();

		NewSprite->PushData(NewImage, Transform);


	}

}

void UImageManager::CuttingSprite(std::string_view KeyName, FVector2D CuttingSize)
{
	std::string UpperName = UEngineString::ToUpper(KeyName);

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("�������� ���� ��������Ʈ�� �ڸ����� �߽��ϴ�. " + std::string(KeyName));
		return;
	}

	if (false == Images.contains(UpperName))
	{
		MSGASSERT("�������� ���� �̹����� ������� ��������Ʈ�� �ڸ����� �߽��ϴ�. " + std::string(KeyName));
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

void UImageManager::CreateCutSprite(std::string_view _SearchKeyName, std::string_view _NewSpriteKeyName, FVector2D _StartPos, FVector2D _CuttingSize, FVector2D _XYOffSet, UINT _Xcount, UINT _ImageCount)
{
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