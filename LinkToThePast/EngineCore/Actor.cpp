#include "PreCompile.h"
#include "Actor.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

#include "EngineSprite.h"
#include <EngineBase/EngineDebug.h>

#include "ImageManager.h"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Render()
{

	if (nullptr == Sprite)
	{
		MSGASSERT("��������Ʈ�� ���õ��� ���� ���͸� �������� �Ҽ� �����ϴ�.");
		return;
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();


	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image;
	CurData.Transform;
	CurData.Image->CopyToTrans(BackBufferImage, Transform, CurData.Transform);
}

void AActor::SetSprite(std::string_view Name, int CurIndex)
{
	Sprite = UImageManager::GetInst().FindSprite(Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� ����Ϸ��� �߽��ϴ�" + std::string(Name));
		return;
	}

	this->CurIndex = CurIndex;
}

