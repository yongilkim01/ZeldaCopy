#pragma once
#include "GameMode.h"
#include <EngineBase/Object.h>

class USpriteRenderer;
class UCollision2D;

class CollisionLinkData
{
public:
	union
	{
		struct
		{
			int Left;
			int Right;
		};
		__int64 Key;
	};
};

/**
*	����
*/
class ULevel : public UObject
{
public:
	friend class UCollision2D;
	friend class USpriteRenderer;
	friend class UEngineAPICore;

	/** ������, �Ҹ��� */
	ULevel();
	~ULevel();

	/** ��ü �� ���� ���� */
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	/** ���� ���� */
	void Tick(float DeltaTime);
	void Render(float DeltaTime);
	void Collision(float DeltaTime);
	void Release(float DeltaTime);

	/** ���� ��ȯ �޼ҵ� */
	void LevelChangeStart();
	void LevelChangeEnd();

	/** ���� Ŭ���� �޼ҵ� */
	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);

		ActorPtr->World = this;

		BeginPlayList.push_back(ActorPtr);

		return NewActor;
	}

	/** �ݸ��� ���� �޼ҵ� */
	template<typename LeftEnumType, typename RightEnumType>
	static void CollisionGroupLink(LeftEnumType Left, RightEnumType Right)
	{
		CollisionGroupLink(static_cast<int>(Left), static_cast<int>(Right));
	}
	static void CollisionGroupLink(int Left, int Right)
	{
		CollisionLinkData LinkData;
		LinkData.Left = Left;
		LinkData.Right = Right;

		for (size_t i = 0; i < CollisionLink.size(); i++)
		{
			if (CollisionLink[i].Key == LinkData.Key)
			{
				return;
			}
		}
		CollisionLink.push_back(LinkData);
	}

	/** �� �� */
	FVector2D GetCameraPivot() 
	{ 
		return this->CameraPivot;
	}
	void SetCameraPivot(FVector2D Pivot)
	{ 
		this->CameraPivot = Pivot; 
	}
	FVector2D GetCameraLocation() 
	{
		return this->CameraLocation;
	}
	void SetCameraLocation(FVector2D Location)
	{
		this->CameraLocation = Location;
	}
	void AddCameraLocation(FVector2D Value) 
	{ 
		this->CameraLocation += Value;
	}
	template<typename ConvertType>
	ConvertType* GetPawn()
	{
		return dynamic_cast<ConvertType*>(MainPawn);
	}
	AActor* GetPawn()
	{
		return MainPawn;
	}
	template<typename ConvertType>
	ConvertType* GetGameMode()
	{
		return dynamic_cast<ConvertType*>(GameMode);
	}
	AActor* GetGameMode()
	{
		return this->GameMode;
	}
	void SetCameraToMainPawn(bool IsCameraToMainPawn)
	{
		this->IsCameraToMainPawn = IsCameraToMainPawn;
	}
	template<typename ActorType>
	std::list<ActorType*> GetActorsFromClass()
	{
		std::list<ActorType*> Result;

		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			ActorType* ConvertActor = dynamic_cast<ActorType*>(CurActor);

			if (nullptr == ConvertActor)
			{
				continue;
			}

			Result.push_back(ConvertActor);
		}
		return Result;
	}

protected:

private:
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		MainPawn = new MainPawnType();

		MainPawn->World = this;
		GameMode->World = this;

		BeginPlayList.push_back(GameMode);
		BeginPlayList.push_back(MainPawn);
	}

	void ScreenClear();
	void DoubleBuffering();
	void BeginPlayCheck();

	void PushRenderer(USpriteRenderer* Renderer);
	void ChangeRenderOrder(USpriteRenderer* Renderer, int PrevOrder);

	void PushCollision(UCollision2D* Collision);
	void PushCheckCollision(UCollision2D* Collision);

	class AGameMode* GameMode = nullptr;
	class AActor* MainPawn = nullptr;

	/** ī�޶� ���� ��� ���� */
	bool IsCameraToMainPawn = false;
	FVector2D CameraLocation = FVector2D::ZERO;
	FVector2D CameraPivot = FVector2D::ZERO;

	std::list<AActor*> AllActors;
	std::list<AActor*> BeginPlayList;

	/** ������ ��ü�� ��� ���� �ڷᱸ�� */
	std::map<int, std::list<class USpriteRenderer*>> Renderers;
	/** �浹ü�� ��Ƴ��� �ڷᱸ�� */
	std::map<int, std::list<class UCollision2D*>> Collisions;
	/** �ݸ��� �׷찣 �浹�� ����� �ڷᱸ�� */
	static std::vector<CollisionLinkData> CollisionLink;
	/** �����Ӹ��� �浹üũ�� �ϴ� �ݸ������� ���� ��� ���� �ڷᱸ�� */
	std::map<int, std::list<class UCollision2D*>> CheckCollisions;
};