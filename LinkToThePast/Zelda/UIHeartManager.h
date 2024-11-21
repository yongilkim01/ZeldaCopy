#pragma once
#include <vector>
#include <EngineCore/Actor.h>

#define MAX_HEART_COUNT 40

class USpriteRenderer;

/**
 *	설명
 */
class AUIHeartManager : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIHeartManager();
	~AUIHeartManager();

	/** 객체 값 복사 방지 */
	AUIHeartManager(const AUIHeartManager& _Other) = delete;
	AUIHeartManager(AUIHeartManager&& _Other) noexcept = delete;
	AUIHeartManager& operator=(const AUIHeartManager& _Other) = delete;
	AUIHeartManager& operator=(AUIHeartManager&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	std::vector<USpriteRenderer*> HeartSprites;
};

