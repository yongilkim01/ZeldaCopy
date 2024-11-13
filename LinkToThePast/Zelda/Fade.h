#pragma once
#include <EngineCore/Actor.h>

/**
 *	����
 */
class AFade : public AActor
{
public:
	static AFade* Instance;

public:
	/** ������, �Ҹ��� */
	AFade();
	~AFade();

	/** ��ü �� ���� ���� */
	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

protected:

private:
	virtual void LevelChangeStart() override;

};

