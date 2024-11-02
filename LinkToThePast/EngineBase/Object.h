#pragma once
#include <string>

/**
 *	엔진 최상위 부모 클래스
 */
class UObject
{
public:
	/** 생성자, 소멸자 */
	UObject();
	virtual ~UObject();

	/** 객체 값 복사 방지 */
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	virtual void SetName(std::string_view _Name) { Name = _Name.data(); }
	std::string GetName() const { return Name; }
	std::string_view GetNameView() const { return Name.c_str(); }

protected:

private:
	std::string Name;
};

