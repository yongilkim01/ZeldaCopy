#include "PreCompile.h"
#include "Level.h"
#include "EngineAPICore.h"
#include "SpriteRenderer.h"
#include "EngineCoreDebug.h"
#include "Collision2D.h"

#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	//{
	//	// BeginPlayList 한번도 체인지 안한 액터는 
	//	// 액터들이 다 비긴 플레이 리스트에 들어가 있다.
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
	BeginPlayCheck();

	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			CurActor->LevelChangeStart();
		}
	}
	{
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			CurActor->LevelChangeStart();
		}
	}
}

void ULevel::LevelChangeEnd()
{
	{
		{
			std::list<AActor*>::iterator StartIter = AllActors.begin();
			std::list<AActor*>::iterator EndIter = AllActors.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				AActor* CurActor = *StartIter;

				CurActor->LevelChangeEnd();
			}
		}

		{
			std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
			std::list<AActor*>::iterator EndIter = BeginPlayList.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				AActor* CurActor = *StartIter;

				// 이건 꺼진애도 호출됩니다.
				CurActor->LevelChangeEnd();
			}
		}
	}
}

void ULevel::Tick(float _DeltaTime)
{
	BeginPlayCheck();

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
			if ((*RenderStartIter)->IsActive() == false)
			{
				continue;
			}

			(*RenderStartIter)->Render(DeltaTime);
		}
	}

	UEngineDebug::PrintEngineDebugRender();

	DoubleBuffering();
}

void ULevel::Release(float DeltaTime)
{
	// 릴리즈 순서는 말단부터 돌려야 합니다.

	// 충돌체 제거
	{
		std::map<int, std::list<class UCollision2D*>>::iterator StartOrderIter = Collisions.begin();
		std::map<int, std::list<class UCollision2D*>>::iterator EndOrderIter = Collisions.end();

		for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
		{
			std::list<class UCollision2D*>& CollisionList = StartOrderIter->second;

			std::list<class UCollision2D*>::iterator CollisionStartIter = CollisionList.begin();
			std::list<class UCollision2D*>::iterator CollisionEndIter = CollisionList.end();

			// 언리얼은 중간에 삭제할수 없어.
			for (; CollisionStartIter != CollisionEndIter; )
			{
				if (false == (*CollisionStartIter)->IsDestroy())
				{
					++CollisionStartIter;
					continue;
				}

				// 랜더러는 지울 필요가 없습니다.
				// (*RenderStartIter) 누가 지울 권한을 가졌느냐.
				// 컴포넌트의 메모리를 삭제할수 권한은 오로지 액터만 가지고 있다.
				CollisionStartIter = CollisionList.erase(CollisionStartIter);
			}
		}
	}

	// 랜더러 제거
	{
		std::map<int, std::list<class USpriteRenderer*>>::iterator StartOrderIter = Renderers.begin();
		std::map<int, std::list<class USpriteRenderer*>>::iterator EndOrderIter = Renderers.end();

		for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
		{
			std::list<class USpriteRenderer*>& RendererList = StartOrderIter->second;

			std::list<class USpriteRenderer*>::iterator RenderStartIter = RendererList.begin();
			std::list<class USpriteRenderer*>::iterator RenderEndIter = RendererList.end();

			// 언리얼은 중간에 삭제할수 없어.
			for (; RenderStartIter != RenderEndIter; )
			{
				if (false == (*RenderStartIter)->IsDestroy())
				{
					++RenderStartIter;
					continue;
				}

				// 랜더러는 지울 필요가 없습니다.
				// (*RenderStartIter) 누가 지울 권한을 가졌느냐.
				// 컴포넌트의 메모리를 삭제할수 권한은 오로지 액터만 가지고 있다.
				RenderStartIter = RendererList.erase(RenderStartIter);
			}
		}
	}

	// 액터 제거
	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; )
		{
			AActor* CurActor = *StartIter;


			if (false == CurActor->IsDestroy())
			{
				CurActor->ReleaseCheck(DeltaTime);
				++StartIter;
				continue;
			}

			// 레벨은 액터의 삭제권한을 가지고 있으니 액터는 진짜 지워 준다.
			delete CurActor;
			StartIter = AllActors.erase(StartIter);
		}
	}
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

void ULevel::BeginPlayCheck()
{
	std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
	std::list<AActor*>::iterator EndIter = BeginPlayList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		if (CurActor->IsActive() == false)
		{
			continue;
		}

		CurActor->BeginPlay();
		AllActors.push_back(CurActor);
	}

	BeginPlayList.clear();

	AActor::ComponentBeginPlay();
}

void ULevel::PushRenderer(USpriteRenderer* Renderer)
{
	int Order = Renderer->GetOrder();

	Renderers[Order].push_back(Renderer);
}

void ULevel::PushCollision(UCollision2D* Collision)
{
	int Order = Collision->GetGroup();
	Collisions[Order].push_back(Collision);
}

void ULevel::ChangeRenderOrder(USpriteRenderer* Renderer, int PrevOrder)
{
	Renderers[PrevOrder].remove(Renderer);

	Renderers[Renderer->GetOrder()].push_back(Renderer);
}

