#pragma once

/**
 *	����
 */
class ArmosKnight
{
public:
	/** ������, �Ҹ��� */
	ArmosKnight();
	~ArmosKnight();

	/** ��ü �� ���� ���� */
	ArmosKnight(const ArmosKnight& _Other) = delete;
	ArmosKnight(ArmosKnight&& _Other) noexcept = delete;
	ArmosKnight& operator=(const ArmosKnight& _Other) = delete;
	ArmosKnight& operator=(ArmosKnight&& _Other) noexcept = delete;

protected:

private:

};

