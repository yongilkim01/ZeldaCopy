#pragma once
#include <random>

/**
 * 
 */
class UEngineRandom
{
public:
	/** ������, �Ҹ��� */
	UEngineRandom();
	~UEngineRandom();

	/** ��ü �� ���� ���� */
	UEngineRandom(const UEngineRandom& Other) = delete;
	UEngineRandom(UEngineRandom&& Other) noexcept = delete;
	UEngineRandom& operator=(const UEngineRandom& Other) = delete;
	UEngineRandom& operator=(UEngineRandom&& Other) noexcept = delete;

	/** ���� �޼ҵ� */
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

	/** ��, �� �޼ҵ� */
	void SetSeed(__int64 Seed)
	{
		std::mt19937_64 MtGen = std::mt19937_64(Seed);
	}
protected:

private:
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));

};