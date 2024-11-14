#pragma once

/**
 *	설명
 */
class ArmosKnight
{
public:
	/** 생성자, 소멸자 */
	ArmosKnight();
	~ArmosKnight();

	/** 객체 값 복사 방지 */
	ArmosKnight(const ArmosKnight& _Other) = delete;
	ArmosKnight(ArmosKnight&& _Other) noexcept = delete;
	ArmosKnight& operator=(const ArmosKnight& _Other) = delete;
	ArmosKnight& operator=(ArmosKnight&& _Other) noexcept = delete;

protected:

private:

};

