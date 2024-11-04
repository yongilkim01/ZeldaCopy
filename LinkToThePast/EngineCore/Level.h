#pragma once
#include "GameMode.h"

/**
* 
*/
class ULevel
{
public:
	friend class USpriteRenderer;
	friend class UEngineAPICore;

	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void LevelChangeStart();

	void LevelChangeEnd();

	void Tick(float _DeltaTime);
	void Render(float DeltaTime);

	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);

		ActorPtr->World = this;

		BeginPlayList.push_back(ActorPtr);

		return NewActor;
	}

	void SetCameraToMainPawn(bool IsCameraToMainPawn) { this->IsCameraToMainPawn = IsCameraToMainPawn; }
	void SetCameraPivot(FVector2D Pivot) { CameraPivot = Pivot; }
	void SetCameraPos(FVector2D _Pos) { CameraPos = _Pos; }
	FVector2D GetCameraPos() { return CameraPos; }
	FVector2D GetCameraPivot() { return CameraPivot; }
	AActor* GetPawn() { return MainPawn; }

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
	void PushRenderer(class USpriteRenderer* Renderer);
	void ChangeRenderOrder(class USpriteRenderer* Renderer, int PrevOrder);

	class AGameMode* GameMode = nullptr;
	class AActor* MainPawn = nullptr;
	std::list<AActor*> AllActors;
	std::list<AActor*> BeginPlayList;

	/** 카메라 관련 멤버 변수 */
	bool IsCameraToMainPawn = false;
	FVector2D CameraPos;
	FVector2D CameraPivot;

	std::map<int, std::list<class USpriteRenderer*>> Renderers;
};