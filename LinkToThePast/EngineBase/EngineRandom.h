#pragma once
#include <random>

/**
 * 
 */
class UEngineRandom
{
public:
	/** 생성자, 소멸자 */
	UEngineRandom();
	~UEngineRandom();

	/** 객체 값 복사 방지 */
	UEngineRandom(const UEngineRandom& Other) = delete;
	UEngineRandom(UEngineRandom&& Other) noexcept = delete;
	UEngineRandom& operator=(const UEngineRandom& Other) = delete;
	UEngineRandom& operator=(UEngineRandom&& Other) noexcept = delete;

	/** 랜덤 메소드 */
	int RandomInt(int Min, int Max)
	{
		std::uniform_int_distribution<int> RandomCreate(Min, Max + 1);
		return RandomCreate.operator()(MtGen);
	}
	float Randomfloat(float Min, float Max)
	{
		std::uniform_real_distribution<float> RandomCreate(Min, Max);
		return RandomCreate.operator()(MtGen);
	}

	/** 겟, 셋 메소드 */
	void SetSeed(__int64 Seed)
	{
		std::mt19937_64 MtGen = std::mt19937_64(Seed);
	}
protected:

private:
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));

};