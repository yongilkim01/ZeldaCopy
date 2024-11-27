#pragma once
#include <EngineCore/Actor.h>
#include "ContentsEnum.h"

class USpriteRenderer;

/**
 *	����
 */
class AUIText : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIText();
	~AUIText();

	/** ��ü �� ���� ���� */
	AUIText(const AUIText& Other) = delete;
	AUIText(AUIText&& Other) noexcept = delete;
	AUIText& operator=(const AUIText& Other) = delete;
	AUIText& operator=(AUIText&& Other) noexcept = delete;

	/** Ŭ���� �޼ҵ� */
	void BeginPlayUIText(std::string_view StrValue, float Time = 0.0f);
	void BeginPlayUIText(const AUIText* UIText);
	void BeginPlayUIText(const std::vector<std::string>& StrValues, float Time = 0.0f);

	void Reserve(int Count);
	void ShowUIText(float DeltaTime);
	void SetOrder(ERenderOrder Order);
	int ConvertCharToIndex(char CharValue);

	/** ��, �� �޼ҵ� */
	std::string GetUIStrValue() const
	{
		return StrValue;
	}
	float GetTime() const
	{
		return Time;
	}
	void SetTime(float Time)
	{
		this->Time = Time;
	}

protected:
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/** ��� ���� �ʱ�ȭ */
	float CurTime = 0.0f;
	float Time = 0.0f;
	int CurCount = 0;

	std::string StrValue;
	const FVector2D TextSize = { 21.0f, 39.0f };
	std::vector<USpriteRenderer*> TextRendereres;
};

