#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class CameraManager
{
public:
	// constrcuter destructer
	CameraManager();
	~CameraManager();

	// delete Function
	CameraManager(const CameraManager& _Other) = delete;
	CameraManager(CameraManager&& _Other) noexcept = delete;
	CameraManager& operator=(const CameraManager& _Other) = delete;
	CameraManager& operator=(CameraManager&& _Other) noexcept = delete;

protected:

private:

};

