#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

/**
 *	설명
 */
class ABaseItem : public AActor
{
public:
	/** 생성자, 소멸자 */
	ABaseItem();
	~ABaseItem();

	/** 객체 값 복사 방지 */
	ABaseItem(const ABaseItem& _Other) = delete;
	ABaseItem(ABaseItem&& _Other) noexcept = delete;
	ABaseItem& operator=(const ABaseItem& _Other) = delete;
	ABaseItem& operator=(ABaseItem&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 아이템 상속 메소드 */
	USpriteRenderer* GetSpriteRenderer()
	{
		return SpriteRenderer;
	}

protected:
	USpriteRenderer* SpriteRenderer = nullptr;

private:

};

