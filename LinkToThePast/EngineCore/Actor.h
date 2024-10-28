#pragma once
#include <EngineBase/EngineMath.h>

// ���� :
class AActor
{
public:
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
	virtual void Tick(float _DeltaTime) {}
	virtual void Render();

	class ULevel* GetWorld()
	{
		return World;
	}

	void SetActorLocation(FVector2D _Location)
	{
		Location = _Location;
	}

	void AddActorLocation(FVector2D _Direction)
	{
		Location += _Direction;
	}

	void SetActorScale(FVector2D _Scale)
	{
		Scale = _Scale;
	}

	FVector2D GetActorLocation()
	{
		return Location;
	}

protected:

private:
	class ULevel* World = nullptr;

	FVector2D Location = FVector2D::ZERO;
	FVector2D Scale = FVector2D::ZERO;
};

