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
*	설명
*/
class ULevel : public UObject
{
public:
	friend class UCollision2D;
	friend class USpriteRenderer;
	friend class UEngineAPICore;

	/** 생성자, 소멸자 */
	ULevel();
	~ULevel();

	/** 객체 값 복사 방지 */
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	/** 엔진 루프 */
	void Tick(float DeltaTime);
	void Render(float DeltaTime);
	void Collision(float DeltaTime);
	void Release(float DeltaTime);

	/** 레벨 전환 메소드 */
	void LevelChangeStart();
	void LevelChangeEnd();

	/** 레벨 클래스 메소드 */
	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);

		ActorPtr->World = this;

		BeginPlayList.push_back(ActorPtr);

		return NewActor;
	}

	/** 콜리전 관련 메소드 */
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

	/** 겟 셋 */
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

	/** 카메라 관련 멤버 변수 */
	bool IsCameraToMainPawn = false;
	FVector2D CameraLocation = FVector2D::ZERO;
	FVector2D CameraPivot = FVector2D::ZERO;

	std::list<AActor*> AllActors;
	std::list<AActor*> BeginPlayList;

	/** 랜더링 객체를 모아 놓은 자료구조 */
	std::map<int, std::list<class USpriteRenderer*>> Renderers;
	/** 충돌체를 모아놓은 자료구조 */
	std::map<int, std::list<class UCollision2D*>> Collisions;
	/** 콜리전 그룹간 충돌을 기록한 자료구조 */
	static std::vector<CollisionLinkData> CollisionLink;
	/** 프레임마다 충돌체크를 하는 콜리전들을 따로 모아 놓은 자료구조 */
	std::map<int, std::list<class UCollision2D*>> CheckCollisions;
};