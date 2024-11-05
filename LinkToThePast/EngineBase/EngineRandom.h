#pragma once
#include <random>

// ���� :
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

	void SetSeed(__int64 _Seed)
	{
		std::mt19937_64 MtGen = std::mt19937_64(_Seed);
	}

	int RandomInt(int _Min, int _Max)
	{
		// _Min ~ _Max ������ �̾���
		std::uniform_int_distribution<int> RandomCreate(_Min, _Max + 1);

		// MtGen ���׷����� �Ἥ
		// std::mt19937_64 �޸��� Ʈ������ �˰��� �Ἥ �������.
		return RandomCreate.operator()(MtGen);
	}

	float Randomfloat(float _Min, float _Max)
	{
		// _Min ~ _Max ������ �̾���
		std::uniform_real_distribution<float> RandomCreate(_Min, _Max);
		return RandomCreate.operator()(MtGen);
	}


protected:

private:
	// std ������
	// ���׷����͸� �������� �մϴ�.

	// �⺻������ Ÿ�ӿ� ���� �õ�� ����
	// ����鼭 new �õ� �־��ݴϴ�.
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));

	//std::well512
};

//
//class MapCreator
//{
//	virtual void MapCreate()
//	{
//
//	}
//};
//
//class RandomMapGenerator
//{
//public:
//	void CreateRandomMap(MapCreator* );
//};
//
//class CaveMapCreator : public MapCreator
//{
//	virtual void MapCreate()
//	{
//
//	}
//};
//
//
//class RoomMapCreator : public MapCreator
//{
//	virtual void MapCreate()
//	{
//
//	}
//};