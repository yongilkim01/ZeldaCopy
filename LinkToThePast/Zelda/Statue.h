#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class ARoom;
/**
 *	설명
 */
class AStatue : public AActor
{
public:
	/** 생성자, 소멸자 */
	AStatue();
	~AStatue();

	/** 객체 값 복사 방지 */
	AStatue(const AStatue& _Other) = delete;
	AStatue(AStatue&& _Other) noexcept = delete;
	AStatue& operator=(const AStatue& _Other) = delete;
	AStatue& operator=(AStatue&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ARoom* GetCurRoom()
	{
		return CurRoom;
	}
	void SetCurRoom(ARoom* Room)
	{
		this->CurRoom = Room;
	}

protected:
	USpriteRenderer* SpriteRenderer = nullptr;

private:
	ARoom* CurRoom = nullptr;
};

