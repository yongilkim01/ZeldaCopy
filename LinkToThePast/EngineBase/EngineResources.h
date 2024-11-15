#pragma once
#include "Object.h"
#include "EnginePath.h"

/**
 *	설명
 */
class UEngineResources : public UObject
{
public:
	/** 생성자, 소멸자 */
	UEngineResources();
	~UEngineResources();

	/** 객체 값 복사 방지 */
	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;

protected:

private:
	UEnginePath Path;
};

