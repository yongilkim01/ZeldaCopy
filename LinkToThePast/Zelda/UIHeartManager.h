#pragma once
#include <vector>
#include <EngineCore/Actor.h>

#define MAX_HEART_COUNT 40

class USpriteRenderer;

/**
 *	����
 */
class AUIHeartManager : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIHeartManager();
	~AUIHeartManager();

	/** ��ü �� ���� ���� */
	AUIHeartManager(const AUIHeartManager& _Other) = delete;
	AUIHeartManager(AUIHeartManager&& _Other) noexcept = delete;
	AUIHeartManager& operator=(const AUIHeartManager& _Other) = delete;
	AUIHeartManager& operator=(AUIHeartManager&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	std::vector<USpriteRenderer*> HeartSprites;
};

