#pragma once

// ���� :
class ULevel
{
public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void Tick()
	{

	}

	void BeginPlay()
	{

	}

protected:

private:
	class AGameMode* GameMode = nullptr;
};

