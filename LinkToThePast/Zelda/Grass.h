#pragma once
#include "EventActor.h"
#include <EnginePlatform/EngineSound.h>

class APlayerCharacter;

enum class EGrassState
{
	NONE,
	LIFT,
	FOLLOW,
	THROW,
};

/**
 *	설명
 */
class AGrass : public AEventActor
{
public:
	/** 생성자, 소멸자 */
	AGrass();
	~AGrass();

	/** 객체 값 복사 방지 */
	AGrass(const AGrass& _Other) = delete;
	AGrass(AGrass&& _Other) noexcept = delete;
	AGrass& operator=(const AGrass& _Other) = delete;
	AGrass& operator=(AGrass&& _Other) noexcept = delete;

	/** 액터 공통 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 이벤트 액터 공통 메소드 */
	virtual int Interact(ABaseCharacter* Character) override;
	virtual void Throw() override;
	virtual void DestoryEventActor() override;

	/** 항아리 액터 상태 머신 메소드 */
	void ChangeState(EGrassState GrassState);

	void StartFollow();
	void StartThrow();

	void Follow(float DeltaTime);
	void Throw(float DeltaTime);

	/** 항아리 액터 유틸 메소드 */
	void EndBreak();
	void SetDropItemType(EDropItemType ItemType)
	{
		DropItemType = ItemType;
	}

	/** 겟, 셋 메소드 */
	void SetIsEvent(bool Value)
	{
		bEvent = Value;
	}
protected:

private:
	EGrassState CurGrassState = EGrassState::NONE;

	APlayerCharacter* Owner = nullptr;
	EDropItemType DropItemType = EDropItemType::NONE;

	USoundPlayer SoundPlayer;

	float ThrowSpeed = 1000.0f;
	bool IsDestorying = false;
	bool bEvent = false;

};

