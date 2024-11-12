#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

/**
 *	설명
 */
class AEffect : public AActor
{
public:
	/** 생성자, 소멸자 */
	AEffect();
	~AEffect();

	/** 객체 값 복사 방지 */
	AEffect(const AEffect& _Other) = delete;
	AEffect(AEffect&& _Other) noexcept = delete;
	AEffect& operator=(const AEffect& _Other) = delete;
	AEffect& operator=(AEffect&& _Other) noexcept = delete;

	virtual void EndEffect() {};

	void SetOwnerActor(AActor* Owner)
	{
		this->OwnerActor = Owner;
	}
	AActor* GetOwnerActor()
	{
		return this->OwnerActor;
	}
	bool GetAnimationIsEnd();

protected:
	USpriteRenderer* SpriteRenderer = nullptr;
private:
	AActor* OwnerActor = nullptr;
};

