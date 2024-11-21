#pragma once

class APlayerCharacter;

/**
 *	설명
 */
class PlayerDataManager
{
public:
	static PlayerDataManager& GetInstance()
	{
		static PlayerDataManager Inst = PlayerDataManager();
		return Inst;
	}

	/** 생성자, 소멸자 */
	~PlayerDataManager();

	/** 객체 값 복사 방지 */
	PlayerDataManager(const PlayerDataManager& _Other) = delete;
	PlayerDataManager(PlayerDataManager&& _Other) noexcept = delete;
	PlayerDataManager& operator=(const PlayerDataManager& _Other) = delete;
	PlayerDataManager& operator=(PlayerDataManager&& _Other) noexcept = delete;

	/** 겟 셋 */
	int GetHP()
	{
		return CurrentHP;
	}
	void SetHP(int HP)
	{
		CurrentHP = HP;
	}
	void AddHP(int Value)
	{
		CurrentHP += Value;
	}
	float GetHPRatio()
	{
		return static_cast<float>(CurrentHP / MaxHP);
	}
	int GetMagicGauge()
	{
		return CurrentMagicGauge;
	}
	void SetMagicGauge(int Gauge)
	{
		CurrentMagicGauge = Gauge;
	}
	void AddMagicGaguge(int Value)
	{
		CurrentMagicGauge += Value;

		if (CurrentMagicGauge > MaxMagicGauge)
		{
			CurrentMagicGauge = MaxMagicGauge;
		}
		else if (CurrentMagicGauge < 0)
		{
			CurrentMagicGauge = 0;
		}
	}
	float GetMagicGaugeRatio()
	{
		return static_cast<float>(CurrentMagicGauge / MaxMagicGauge);
	}

protected:

private:
	PlayerDataManager();

	APlayerCharacter* Player = nullptr;

	int CurrentHP = 100;
	int MaxHP = 100;

	int CurrentMagicGauge = 105;
	const int MaxMagicGauge = 105;
};

