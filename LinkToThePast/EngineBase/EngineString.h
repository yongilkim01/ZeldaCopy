#pragma once
#include <string>

/**
 *	�������� ����ϴ� ���ڿ� ���� ��� Ŭ����
 */
class UEngineString
{
public:
	~UEngineString();

	/** ��ü �� ���� ���� */
	UEngineString(const UEngineString& Other) = delete;
	UEngineString(UEngineString&& Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& Other) = delete;
	UEngineString& operator=(UEngineString&& Other) noexcept = delete;

	/** �빮�� ��ȯ �޼ҵ� */
	static std::string ToUpper(std::string_view);
	/** �����ڵ� ��ȯ �޼ҵ� */
	static std::wstring AnsiToUnicode(std::string_view Name);
protected:

private:
	UEngineString();
};

