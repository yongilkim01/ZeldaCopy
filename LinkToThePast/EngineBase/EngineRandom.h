#pragma once

// Ό³Έν :
class UEngineRandom
{
public:
	// constrcuter destructer
	UEngineRandom();
	~UEngineRandom();

	// delete Function
	UEngineRandom(const UEngineRandom& _Other) = delete;
	UEngineRandom(UEngineRandom&& _Other) noexcept = delete;
	UEngineRandom& operator=(const UEngineRandom& _Other) = delete;
	UEngineRandom& operator=(UEngineRandom&& _Other) noexcept = delete;

protected:

private:

};

