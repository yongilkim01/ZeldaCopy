#pragma once
#include <EngineCore/EngineAPICore.h>
/**
 *	설명
 */
class UZeldaCore : public UContentsCore
{
public:
	/** 생성자, 소멸자 */
	UZeldaCore();
	~UZeldaCore();

	/** 객체 값 복사 방지 */
	UZeldaCore(const UZeldaCore& _Other) = delete;
	UZeldaCore(UZeldaCore&& _Other) noexcept = delete;
	UZeldaCore& operator=(const UZeldaCore& _Other) = delete;
	UZeldaCore& operator=(UZeldaCore&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:
	ULevel* TitleLevel = nullptr;
};

