#pragma once

class APlayerCharacter;

/**
 *	����
 */
class PlayerDataManager
{
public:
	static PlayerDataManager& GetInstance()
	{
		static PlayerDataManager Inst = PlayerDataManager();
		return Inst;
	}

	/** ������, �Ҹ��� */
	~PlayerDataManager();

	/** ��ü �� ���� ���� */
	PlayerDataManager(const PlayerDataManager& _Other) = delete;
	PlayerDataManager(PlayerDataManager&& _Other) noexcept = delete;
	PlayerDataManager& operator=(const PlayerDataManager& _Other) = delete;
	PlayerDataManager& operator=(PlayerDataManager&& _Other) noexcept = delete;

	/** �� �� */
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

		if (CurrentHP > MaxHP)
		{
			CurrentHP = MaxHP;
		}
		else if (CurrentHP < 0)
		{
			CurrentHP = 0;
		}
	}
	float GetHPRatio()
	{
		return static_cast<float>(CurrentHP / MaxHP);
	}
	int GetMaxHP()
	{
		return MaxHP;
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
	void AddRupee(int Rupee)
	{
		CurrentRupee += Rupee;
	}
	int GetRupee()
	{
		return CurrentRupee;
	}

protected:

private:
	PlayerDataManager();

	APlayerCharacter* Player = nullptr;

	int CurrentHP = 6;
	int MaxHP = 6;

	int CurrentMagicGauge = 105;
	const int MaxMagicGauge = 105;

	int CurrentRupee = 10;
};
