#pragma once
#include "SceneComponent.h"

// ���� :
class USpriteRenderer : public USceneComponent
{
	// �ְ� �� ����Ѵ�.
	// Ŭ������ ��ȭ�з��ؼ�
public:
	class FrameAnimation
	{
	public:
		UEngineSprite* Sprite = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;
		std::map<int, EngineDelegate> Events;

		int CurIndex = 0;
		int ResultIndex = 0;
		float CurTime = 0.0f;
		bool Loop = true;

		void Reset()
		{
			CurIndex = 0;
			CurTime = 0;
			ResultIndex = 0;
		}
	};


public:
	// constrcuter destructer
	USpriteRenderer();
	~USpriteRenderer();

	// delete Function
	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void Render(float _DeltaTime);
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;

	bool IsActive() override
	{
		// �������� �ڽ��� ���� ���Ϳ��� ���ӵȴ�.
		// �θ�        true            true
		return UObject::IsActive() && GetActor()->IsActive();
	}

	bool IsDestroy() override
	{
		// �θ�        true            true
		return UObject::IsDestroy() || GetActor()->IsDestroy();
	}

	// int�� �ִ� �Լ����� �Ϲ������� Enum���� ��ü�ؼ� �ְ� �������� ����.
	// �׷��� �װ� Ŀ���� ����� ����� ����� �ڽŸ��� enum�� ���̱� ������ 
	// ���ø��� ����Ͽ� � enum�̰� �ް� ����� ����� ��ȣ�Ѵ�.
	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	int GetOrder()
	{
		return Order;
	}
	std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}

	void SetCameraEffect(bool Value)
	{
		IsCameraEffect = Value;
	}

	void SetCameraEffectScale(float Effect);
	void SetSprite(std::string_view Name, int CurIndex = 0);


	FVector2D SetSpriteScale(float _Ratio = 1.0f, int _CurIndex = 0);


	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time = 0.1f, bool _Loop = true);

	// _AnimationName �̸��� �ִϸ��̼��� ������.
	// _SpriteName �� �̸��� ��������Ʈ��
	// _Indexs �������� �̳༮���� ����ؼ�   0     1      2     3     4     5 
	// _Frame �� �ð��� �����                 0.1    0.1    0.1   0.1  0.1   0.1
	// _Loop = true�� �ݺ� false�� ������ �����ӿ��� ����
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);

	// ���� Idle�ε� Idle �ٲٶ�� �ߴ�. 
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop = true);

	void SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function);

protected:

public:
	int Order = 0;
	int CurIndex = 0;
	bool IsCameraEffect = true;
	float CameraEffectScale = 1.0f;

	class UEngineSprite* Sprite = nullptr;

	std::map<std::string, FrameAnimation> FrameAnimations;
	FrameAnimation* CurAnimation = nullptr;
};

