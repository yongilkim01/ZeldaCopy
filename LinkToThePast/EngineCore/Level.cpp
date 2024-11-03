#include "PreCompile.h"
#include "Level.h"
#include "EngineAPICore.h"
#include "SpriteRenderer.h"
#include "EngineCoreDebug.h"

#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	//{
	//	// BeginPlayList �ѹ��� ü���� ���� ���ʹ� 
	//	// ���͵��� �� ��� �÷��� ����Ʈ�� �� �ִ�.
	//	std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
	//	std::list<AActor*>::iterator EndIter = BeginPlayList.end();
	//	for (; StartIter != EndIter; ++StartIter)
	//	{
	//		AActor* CurActor = *StartIter;
	//		delete CurActor;
	//	}
	//}
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		if (nullptr != CurActor)
		{
			delete* StartIter;
		}
	}
}

void ULevel::LevelChangeStart()
{
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;
		CurActor->LevelChangeStart();
	}
}

void ULevel::LevelChangeEnd()
{
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;
		CurActor->LevelChangeEnd();
	}
}

void ULevel::Tick(float _DeltaTime)
{
	{
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			CurActor->BeginPlay();
			AllActors.push_back(CurActor);
		}

		BeginPlayList.clear();

		AActor::ComponentBeginPlay();
	}

	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			CurActor->Tick(_DeltaTime);
		}
	}
}

void ULevel::Render(float DeltaTime)
{
	ScreenClear();

	if (IsCameraToMainPawn == true)
	{
		// CameraPivot = FVector2D(-1280, -720) * 0.5f;
		//CameraPos = MainPawn->GetTransform().Location + CameraPivot;
	}

	std::map<int, std::list<class USpriteRenderer*>>::iterator StartOrderIter = Renderers.begin();
	std::map<int, std::list<class USpriteRenderer*>>::iterator EndOrderIter = Renderers.end();

	for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
	{
		std::list<class USpriteRenderer*>& RendererList = StartOrderIter->second;

		std::list<class USpriteRenderer*>::iterator RenderStartIter = RendererList.begin();
		std::list<class USpriteRenderer*>::iterator RenderEndIter = RendererList.end();

		for (; RenderStartIter != RenderEndIter; ++RenderStartIter)
		{
			(*RenderStartIter)->Render(DeltaTime);
		}
	}

	UEngineDebug::PrintEngineDebugText();

	DoubleBuffering();
}

void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	FVector2D Size = MainWindow.GetWindowSize();

	//Rectangle(BackBufferImage->GetDC(), 0, 0, Size.iX(), Size.iY());
	Rectangle(BackBufferImage->GetDC(), -1, -1, Size.iX() + 2, Size.iY() + 2);
}

void ULevel::DoubleBuffering()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();

	UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();

	FTransform Trans;
	Trans.Location = MainWindow.GetWindowSize().Half();
	Trans.Scale = MainWindow.GetWindowSize();

	BackBufferImage->CopyToBit(WindowImage, Trans);
}

void ULevel::PushRenderer(USpriteRenderer* Renderer)
{
	int Order = Renderer->GetOrder();

	Renderers[Order].push_back(Renderer);
}

void ULevel::ChangeRenderOrder(USpriteRenderer* Renderer, int PrevOrder)
{
	Renderers[PrevOrder].remove(Renderer);

	Renderers[Renderer->GetOrder()].push_back(Renderer);
}

