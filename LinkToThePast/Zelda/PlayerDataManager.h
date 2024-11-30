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

	void AddKey(int Key)
	{
		CurrentKey += Key;

		if (CurrentKey > MaxKey)
		{
			CurrentKey = MaxKey;
		}
		else if (CurrentKey < 0)
		{
			CurrentKey = 0;
		}
	}
	int GetKey()
	{
		return CurrentKey;
	}

	bool GetWeaponActiveToIndex(int Index)
	{
		if (0 <= Index && Index < 2)
		{
			return WeaponActive[Index];
		}
		return false;
	}

	void SetWeaponActiveToIndex(int Index, bool Value)
	{
		if (0 <= Index && Index < 2)
		{
			WeaponActive[Index] = Value;
		}
	}

	int GetSelectWeapon()
	{
		return CurrentSelectWeapon;
	}
	void SetSelectWeapon(int Index)
	{
		this->CurrentSelectWeapon = Index;
	}
	void AddSelectWeapon(int Index)
	{
		if (0 == WeaponCount) return;

		this->CurrentSelectWeapon += Index;

		if (CurrentSelectWeapon >= WeaponCount)
		{
			CurrentSelectWeapon = WeaponCount - 1;
		}
		else if (CurrentSelectWeapon < 0)
		{
			CurrentSelectWeapon = 0;
		}
	}
	int GetWeaponCount()
	{
		return WeaponCount;
	}
	void AddWeaponCount(int Count)
	{
		WeaponCount += Count;
	}

	void SetLevelStartLocation(FVector2D Location)
	{
		LevelStartLocation = Location;
	}
	FVector2D GetLevelStartLocation()
	{
		return LevelStartLocation;
	}
	void SetLevelStartRoomIndex(int Index)
	{
		LevelStartRoomIndex = Index;
	}
	int GetLevelStartRoomIndex()
	{
		return LevelStartRoomIndex;
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

	int CurrentKey = 3;
	int MaxKey = 9;

	//bool WeaponActive[2]  ={
	//	false,	// Lantern
	//	false	// Bow
	//};

	//int CurrentSelectWeapon = -1;
	//int WeaponCount = 0;

	bool WeaponActive[2] = {
	true,	// Lantern
	true	// Bow
	};

	int CurrentSelectWeapon = 0;
	int WeaponCount = 2;

	FVector2D LevelStartLocation = FVector2D::ZERO;
	int LevelStartRoomIndex = -1;
};

