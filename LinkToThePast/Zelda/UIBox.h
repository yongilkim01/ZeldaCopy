#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class AUIText;

enum class EUIBoxState
{
	NONE,
	SHOW,
	END,
};

/**
 *	설명
 */
class AUIBox : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIBox();
	~AUIBox();

	/** 객체 값 복사 방지 */
	AUIBox(const AUIBox& _Other) = delete;
	AUIBox(AUIBox&& _Other) noexcept = delete;
	AUIBox& operator=(const AUIBox& _Other) = delete;
	AUIBox& operator=(AUIBox&& _Other) noexcept = delete;

	/** 클래스 상태 메소드 */
	void StartShow();
	void StartEnd();

	void Show(float DeltaTime);
	void End(float DeltaTime);

	void ChangeState(EUIBoxState State);

	/** 클래스 메소드 */
	void CreateUIText(std::string_view StrValue, float Time = 0.0f);
	void CreateUIText(const std::vector<std::string>& StrValues, float Time = 0.0f);
	void SetUIText(std::string_view StrValue, int Index = 0, float Time = 0.0f);
	void SetUIText(const std::vector<std::string>& StrValues, int Index = 0, float Time = 0.0f);
	//void ShowUI(float DeltaTime = 0.0f);
	void HideUI();

	/** 겟, 셋 메소드 */
	void SetTextsCount(int Count);

	std::vector<AUIText*>::iterator GetCurTextIter()
	{
		return UITextIter;
	}
	void ResetTextIter()
	{
		UITextIter = UITextes.begin();
	}
	void NextTextIter() 
	{
		++UITextIter;
		if (UITextIter == UITextes.end()) {
			UITextIter = UITextes.begin();
		}
	}
	void PrevTextIter()
	{
		if (UITextIter == UITextes.begin()) {
			UITextIter = UITextes.end();
		}
		--UITextIter;
	}
	void SetTime(float Time)
	{
		this->Time = Time;
	}
	float GetTime()
	{
		return Time;
	}

protected:
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	std::vector<AUIText*> UITextes;
	std::vector<AUIText*>::iterator UITextIter;

	USpriteRenderer* BoxRenderer = nullptr;

	float CurTime = 0.0f;
	float Time = 0.0f;
	int CurLineCount = 0;
	int MaxLineCount = 0;
	EUIBoxState CurState = EUIBoxState::NONE;
};

