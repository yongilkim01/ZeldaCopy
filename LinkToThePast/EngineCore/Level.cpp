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
	{
		// BeginPlayList �ѹ��� ü���� ���� ���ʹ� 
		// ���͵��� �� ��� �÷��� ����Ʈ�� �� �ִ�.
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			delete CurActor;
		}
	}
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

				// �̰� �����ֵ� ȣ��˴ϴ�.
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

			if (CurActor->IsActive() == false)
			{
				continue;
			}

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

void ULevel::Collision(float DeltaTime)
{
	for (size_t i = 0; i < CollisionLink.size(); i++)
	{
		CollisionLinkData Data = CollisionLink[i];

		int Left = Data.Left;
		int Right = Data.Right;

		// �̺�Ʈ�� �浹üũ�ϴ� �׷�
		std::list<class UCollision2D*>& LeftList = CheckCollisions[Left];

		// �� ����� �̺�Ʈ �׷��� �ƴϾ �ǹǷ� �׳� �ݸ��� �������� �����´�.
		std::list<class UCollision2D*>& RightList = Collisions[Right];

		std::list<class UCollision2D*>::iterator StartLeftIter = LeftList.begin();
		std::list<class UCollision2D*>::iterator EndLeftIter = LeftList.end();

		std::list<class UCollision2D*>::iterator EndRightIter = RightList.end();

		for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
		{
			UCollision2D* LeftCollision = *StartLeftIter;

			if (false == LeftCollision->IsActive())
			{
				continue;
			}

			std::list<class UCollision2D*>::iterator StartRightIter = RightList.begin();

			for (; StartRightIter != EndRightIter; ++StartRightIter)
			{
				UCollision2D* RightCollision = *StartRightIter;
				if (LeftCollision == RightCollision)
				{
					continue;
				}

				if (false == RightCollision->IsActive())
				{
					continue;
				}

				LeftCollision->CollisionEventCheck(RightCollision);
			}
		}
	}
}

void ULevel::Release(float DeltaTime)
{
	// ������ ������ ���ܺ��� ������ �մϴ�.
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;
		CurActor->ReleaseTimeCheck(DeltaTime);
	}

	// �浹ü ����
	{
		std::map<int, std::list<class UCollision2D*>>::iterator StartOrderIter = Collisions.begin();
		std::map<int, std::list<class UCollision2D*>>::iterator EndOrderIter = Collisions.end();

		for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
		{
			std::list<class UCollision2D*>& CollisionList = StartOrderIter->second;

			std::list<class UCollision2D*>::iterator CollisionStartIter = CollisionList.begin();
			std::list<class UCollision2D*>::iterator CollisionEndIter = CollisionList.end();

			// �𸮾��� �߰��� �����Ҽ� ����.
			for (; CollisionStartIter != CollisionEndIter; )
			{
				bool TestBoolean = (*CollisionStartIter)->IsDestroy();
				if (false == (*CollisionStartIter)->IsDestroy())
				{
					++CollisionStartIter;
					continue;
				}

				// �������� ���� �ʿ䰡 �����ϴ�.
				// (*RenderStartIter) ���� ���� ������ ��������.
				// ������Ʈ�� �޸𸮸� �����Ҽ� ������ ������ ���͸� ������ �ִ�.
				CollisionStartIter = CollisionList.erase(CollisionStartIter);
			}
		}
	}
	// �̺�Ʈ �浹ü ����
	{
		std::map<int, std::list<class UCollision2D*>>::iterator StartOrderIter = CheckCollisions.begin();
		std::map<int, std::list<class UCollision2D*>>::iterator EndOrderIter = CheckCollisions.end();

		for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
		{
			std::list<class UCollision2D*>& CollisionList = StartOrderIter->second;

			std::list<class UCollision2D*>::iterator CollisionStartIter = CollisionList.begin();
			std::list<class UCollision2D*>::iterator CollisionEndIter = CollisionList.end();

			for (; CollisionStartIter != CollisionEndIter; )
			{
				if (false == (*CollisionStartIter)->IsDestroy())
				{
					++CollisionStartIter;
					continue;
				}

				CollisionStartIter = CollisionList.erase(CollisionStartIter);
			}
		}
	}
	// ������ ����
	{
		std::map<int, std::list<class USpriteRenderer*>>::iterator StartOrderIter = Renderers.begin();
		std::map<int, std::list<class USpriteRenderer*>>::iterator EndOrderIter = Renderers.end();

		for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
		{
			std::list<class USpriteRenderer*>& RendererList = StartOrderIter->second;

			std::list<class USpriteRenderer*>::iterator RenderStartIter = RendererList.begin();
			std::list<class USpriteRenderer*>::iterator RenderEndIter = RendererList.end();

			for (; RenderStartIter != RenderEndIter; )
			{
				if (false == (*RenderStartIter)->IsDestroy())
				{
					++RenderStartIter;
					continue;
				}

				RenderStartIter = RendererList.erase(RenderStartIter);
			}
		}
	}
	// ���� ����
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

std::vector<CollisionLinkData> ULevel::CollisionLink;

void ULevel::PushCheckCollision(UCollision2D* Collision)
{
	int Order = Collision->GetGroup();
	CheckCollisions[Order].push_back(Collision);
}

void ULevel::ChangeRenderOrder(USpriteRenderer* Renderer, int PrevOrder)
{
	Renderers[PrevOrder].remove(Renderer);

	Renderers[Renderer->GetOrder()].push_back(Renderer);
}

