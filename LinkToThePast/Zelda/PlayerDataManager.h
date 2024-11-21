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

		if (CurrentRupee > MaxRupee)
		{
			CurrentRupee = MaxRupee;
		}
		else if (CurrentRupee < 0)
		{
			CurrentRupee = 0;
		}
	}
	int GetRupee()
	{
		return CurrentRupee;
	}

	void AddBomb(int Bomb)
	{
		CurrentBomb += Bomb;

		if (CurrentBomb > MaxBomb)
		{
			CurrentBomb = MaxBomb;
		}
		else if (CurrentBomb < 0)
		{
			CurrentBomb = 0;
		}
	}
	int GetBomb()
	{
		return CurrentBomb;
	}

	void AddArrow(int Arrow)
	{
		CurrentArrow += Arrow;

		if (CurrentArrow > MaxArrow)
		{
			CurrentArrow = MaxArrow;
		}
		else if (CurrentArrow < 0)
		{
			CurrentArrow = 0;
		}
	}
	int GetArrow()
	{
		return CurrentArrow;
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
	int MaxRupee = 999;

	int CurrentBomb = 3;
	int MaxBomb = 99;

	int CurrentArrow = 3;
	int MaxArrow = 99;
};

