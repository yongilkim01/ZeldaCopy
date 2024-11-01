#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ARoomManageMode : public AGameMode
{
public:
	// constrcuter destructer
	ARoomManageMode();
	~ARoomManageMode();

	// delete Function
	ARoomManageMode(const ARoomManageMode& _Other) = delete;
	ARoomManageMode(ARoomManageMode&& _Other) noexcept = delete;
	ARoomManageMode& operator=(const ARoomManageMode& _Other) = delete;
	ARoomManageMode& operator=(ARoomManageMode&& _Other) noexcept = delete;

	void BeginPlay();

protected:

private:

};