#pragma once
#include <EngineCore/EngineAPICore.h>

// Ό³Έν :
class ZeldaContentsCore : public UContentsCore
{
public:
	// constrcuter destructer
	ZeldaContentsCore();
	~ZeldaContentsCore();

	// delete Function
	ZeldaContentsCore(const ZeldaContentsCore& _Other) = delete;
	ZeldaContentsCore(ZeldaContentsCore&& _Other) noexcept = delete;
	ZeldaContentsCore& operator=(const ZeldaContentsCore& _Other) = delete;
	ZeldaContentsCore& operator=(ZeldaContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:

};

