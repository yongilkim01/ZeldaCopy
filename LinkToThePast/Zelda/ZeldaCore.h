#pragma once
#include <EngineCore/EngineAPICore.h>
/**
 *	����
 */
class UZeldaCore : public UContentsCore
{
public:
	/** ������, �Ҹ��� */
	UZeldaCore();
	~UZeldaCore();

	/** ��ü �� ���� ���� */
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

