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
 *	����
 */
class AUIBox : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIBox();
	~AUIBox();

	/** ��ü �� ���� ���� */
	AUIBox(const AUIBox& _Other) = delete;
	AUIBox(AUIBox&& _Other) noexcept = delete;
	AUIBox& operator=(const AUIBox& _Other) = delete;
	AUIBox& operator=(AUIBox&& _Other) noexcept = delete;

	/** Ŭ���� ���� �޼ҵ� */
	void StartShow();
	void StartEnd();

	void Show(float DeltaTime);
	void End(float DeltaTime);

	void ChangeState(EUIBoxState State);

	/** Ŭ���� �޼ҵ� */
	void CreateUIText(std::string_view StrValue, float Time = 0.0f);
	void CreateUIText(const std::vector<std::string>& StrValues, float Time = 0.0f);
	void SetUIText(std::string_view StrValue, int Index = 0, float Time = 0.0f);
	void SetUIText(const std::vector<std::string>& StrValues, int Index = 0, float Time = 0.0f);
	//void ShowUI(float DeltaTime = 0.0f);
	void HideUI();

	/** ��, �� �޼ҵ� */
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
	/** ���� ��� �޼ҵ� */
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

