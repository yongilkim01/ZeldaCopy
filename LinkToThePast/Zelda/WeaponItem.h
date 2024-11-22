#pragma once
#include "BaseItem.h"

class USpriteRenderer;

/**
 *	설명
 */
class AWeaponItem : public ABaseItem
{
public:
	/** 생성자, 소멸자 */
	AWeaponItem();
	~AWeaponItem();

	/** 객체 값 복사 방지 */
	AWeaponItem(const AWeaponItem& _Other) = delete;
	AWeaponItem(AWeaponItem&& _Other) noexcept = delete;
	AWeaponItem& operator=(const AWeaponItem& _Other) = delete;
	AWeaponItem& operator=(AWeaponItem&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 웨폰 액터 상속 메소드 */
	void SetId(int Id)
	{
		this->Id = Id;
	}
	int GetId()
	{
		return this->Id;
	}
	USpriteRenderer* GetUISpriteRenderer()
	{
		return this->UISpriteRenderer;
	}
	
	std::string GetUISpriteName()
	{
		return UISpriteName;
	}

protected:
	USpriteRenderer* UISpriteRenderer = nullptr;
	std::string UISpriteName;

private:
	int Id = 0;
};

