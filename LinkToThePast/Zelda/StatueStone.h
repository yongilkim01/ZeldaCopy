#pragma once
#include "Statue.h"

/**
 *	설명
 */
class AStatueStone : public AStatue
{
public:
	/** 생성자, 소멸자 */
	AStatueStone();
	~AStatueStone();

	/** 객체 값 복사 방지 */
	AStatueStone(const AStatueStone& _Other) = delete;
	AStatueStone(AStatueStone&& _Other) noexcept = delete;
	AStatueStone& operator=(const AStatueStone& _Other) = delete;
	AStatueStone& operator=(AStatueStone&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:

};

