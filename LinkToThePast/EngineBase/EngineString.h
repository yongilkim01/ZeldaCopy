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
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;

	/** �빮�� ��ȯ �޼ҵ� */
	static std::string ToUpper(std::string_view);
	/** �����ڵ� ��ȯ �޼ҵ� */
	static std::wstring AnsiToUnicode(std::string_view _Name);
protected:

private:
	UEngineString();
};

