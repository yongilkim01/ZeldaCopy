#pragma once
#include <string>

/**
 *	���� �ֻ��� �θ� Ŭ����
 */
class UObject
{
public:
	/** ������, �Ҹ��� */
	UObject();
	virtual ~UObject();

	/** ��ü �� ���� ���� */
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

