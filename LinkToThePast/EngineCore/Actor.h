#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/TimeEvent.h>

#include "EngineSprite.h"

class ULevel;

// 설명 :
class AActor : public UObject
{
public:
	typedef AActor Super;
	friend class ULevel;

	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	virtual void BeginPlay() {}
	virtual void Tick(float _DeltaTime);

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject()
	{
		ComponentType* NewComponent = new ComponentType();

		UActorComponent* ComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);
		// 내가 널 만든 레벨이야.
		ComponentPtr->ParentActor = this;

		// 생성될때 하지 않습니다.
		// NewComponent->BeginPlay();
		// 만들기만 하고 실행 안한 상태가 된것.
		Components.push_back(NewComponent);

		// BeginPlay가 실행안된 컴포넌트들을 다 자료구조에 담는다.
		ComponentList.push_back(NewComponent);
		return NewComponent;


	}

	ULevel* GetWorld() 
	{ 
		return World; 
	}
	FVector2D GetActorLocation() 
	{
		return Transform.Location;
	}
	void SetActorLocation(FVector2D Location) 
	{
		Transform.Location = Location;
	}
	void AddActorLocation(FVector2D Direction) 
	{
		Transform.Location += Direction;
	}
	FTransform GetTransform() 
	{ 
		return Transform; 
	}

protected:
	UTimeEvent TimeEventer;

private:
	static void ComponentBeginPlay();
	static bool IsNewActorCreate;
	static std::list<class UActorComponent*> ComponentList;

	virtual void ReleaseCheck(float _DeltaTime) override;
	virtual void ReleaseTimeCheck(float _DeltaTime) override;

	class ULevel* World = nullptr;
	FTransform Transform;

	std::list<class UActorComponent*> Components;
};