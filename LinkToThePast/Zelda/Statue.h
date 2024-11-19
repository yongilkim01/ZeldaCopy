#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class ARoom;
/**
 *	����
 */
class AStatue : public AActor
{
public:
	/** ������, �Ҹ��� */
	AStatue();
	~AStatue();

	/** ��ü �� ���� ���� */
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

