#pragma once
#include <EngineCore/Actor.h>

/**
 *	설명
 */
class ABossCharacter : public AActor
{
public:
	/** 생성자, 소멸자 */
	ABossCharacter();
	~ABossCharacter();

	/** 객체 값 복사 방지 */
	ABossCharacter(const ABossCharacter& _Other) = delete;
	ABossCharacter(ABossCharacter&& _Other) noexcept = delete;
	ABossCharacter& operator=(const ABossCharacter& _Other) = delete;
	ABossCharacter& operator=(ABossCharacter&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

};

