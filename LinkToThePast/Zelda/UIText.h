#pragma once
#include <EngineCore/Actor.h>
#include "ContentsEnum.h"

enum class EUITExtState
{
	NONE,
	IDLE,
	MOVE,
};

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

	/** 상태 메소드 */
	void StartIdle();
	void StartMove();

	void Idle(float DeltaTime);
	void Move(float DeltaTime);

	void ChangeState(EUITExtState State);

	/** 클래스 메소드 */
	void BeginPlayUIText(std::string_view StrValue, float Time = 0.0f);
	void BeginPlayUIText(const AUIText* UIText);
	void BeginPlayUIText(const std::vector<std::string>& StrValues, float Time = 0.0f);

	void Reserve(int Count);
	void ShowUIText(float DeltaTime);
	void HideUIText(float DeltaTime);
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
	float MoveFrequency = 0.1f;
	float HorizontalPadding = 35.0f;

	std::string StrValue;
	const FVector2D TextSize = { 15.0f, 30.0f };
	const FVector2D MoveDir = FVector2D::UP;
	FVector2D StartLocation = FVector2D::ZERO;
	FVector2D EndLocation = FVector2D::ZERO;
	std::vector<USpriteRenderer*> TextRendereres;
	

	EUITExtState CurState = EUITExtState::NONE;
};

