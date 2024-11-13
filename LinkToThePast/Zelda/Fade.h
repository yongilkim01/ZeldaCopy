#pragma once
#include <EngineCore/Actor.h>

/**
 *	설명
 */
class AFade : public AActor
{
public:
	static AFade* Instance;

public:
	/** 생성자, 소멸자 */
	AFade();
	~AFade();

	/** 객체 값 복사 방지 */
	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

protected:

private:
	virtual void LevelChangeStart() override;

};

