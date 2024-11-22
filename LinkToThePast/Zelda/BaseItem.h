#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

/**
 *	����
 */
class ABaseItem : public AActor
{
public:
	/** ������, �Ҹ��� */
	ABaseItem();
	~ABaseItem();

	/** ��ü �� ���� ���� */
	ABaseItem(const ABaseItem& _Other) = delete;
	ABaseItem(ABaseItem&& _Other) noexcept = delete;
	ABaseItem& operator=(const ABaseItem& _Other) = delete;
	ABaseItem& operator=(ABaseItem&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ������ ��� �޼ҵ� */
	USpriteRenderer* GetSpriteRenderer()
	{
		return SpriteRenderer;
	}

protected:
	USpriteRenderer* SpriteRenderer = nullptr;

private:

};

