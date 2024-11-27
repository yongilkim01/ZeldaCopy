#pragma once
#include <EngineCore/Actor.h>
#include "ContentsEnum.h"

class USpriteRenderer;

/**
 *	설명
 */
class AUIText : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIText();
	~AUIText();

	/** 객체 값 복사 방지 */
	AUIText(const AUIText& Other) = delete;
	AUIText(AUIText&& Other) noexcept = delete;
	AUIText& operator=(const AUIText& Other) = delete;
	AUIText& operator=(AUIText&& Other) noexcept = delete;

	/** 클래스 메소드 */
	void BeginPlayUIText(std::string_view StrValue, float Time = 0.0f);
	void BeginPlayUIText(const AUIText* UIText);
	void BeginPlayUIText(const std::vector<std::string>& StrValues, float Time = 0.0f);

	void Reserve(int Count);
	void ShowUIText(float DeltaTime);
	void SetOrder(ERenderOrder Order);
	int ConvertCharToIndex(char CharValue);

	/** 겟, 셋 메소드 */
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
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/** 멤버 변수 초기화 */
	float CurTime = 0.0f;
	float Time = 0.0f;
	int CurCount = 0;

	std::string StrValue;
	const FVector2D TextSize = { 21.0f, 39.0f };
	std::vector<USpriteRenderer*> TextRendereres;
};

