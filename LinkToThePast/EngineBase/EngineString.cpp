#include "PreCompile.h"
#include "EngineString.h"
#include <EngineBase/EngineDebug.h>

UEngineString::UEngineString()
{
}

UEngineString::~UEngineString()
{
}


std::string UEngineString::ToUpper(std::string_view Str)
{
	std::string Result = Str.data();
	Result.resize(Str.size());

	for (size_t i = 0; i < Str.size(); i++)
	{
		Result[i] = std::toupper(Str[i]);
	}

	return Result;
}

std::wstring UEngineString::AnsiToUnicode(std::string_view Str)
{
	// �����찡 �������ٱ�?
	// �⺻������ ��κ��� �ü���� �������ڵ� �����
	// �����ڵ忡 ���ؼ� �����ȴ�.
	// ��κ� �ü���� 2����Ʈ�� ����ǥ���� �Ѱ�� ���ϴ�.
	// �����ڵ带 �����ϴ°��� => OS

	// ��Ƽ����Ʈ�� ���̵� ����Ʈ�� �ٲ��ִ� Ŭ�����Դϴ�.
	// CP_ACP ���� �����ڵ带 ������� �������ּ���.

	// ��Ƽ����Ʈ 200����Ʈ => 1~2����Ʈ�� ǥ���ϴ� �༮ => ���̵� ����Ʈ�� �ٲ۴ٰ�
	//  400����Ʈ
	// �ٲٷ��� �����Ʈ�� �ʿ������� �˾Ƴ��ִ� �Լ��� �ʿ��ϰڳ׿�?

	//�� �Լ��� 2���� ������ ���մϴ�.
	// std::wstring => std::vector<wchar_t> ;

	// ������ 2���� ������
	// �ޱ����� ���̵����Ʈ �޸𸮿�
	// �� �޸��� ũ�⸦ �־��ָ�
	// ��ȯ�� ũ�Ⱑ �󸶰� �Ǵ��� ������ִ� �Լ��� ����˴ϴ�.
	int Size = MultiByteToWideChar(CP_ACP, 0, Str.data(), static_cast<int>(Str.size()), nullptr, 0);

	if (0 == Size)
	{
		MSGASSERT("MultiByteToWideChar ���ڿ� ��ȯ�� �����߽��ϴ�" + std::string(Str));
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, Str.data(), static_cast<int>(Str.size()), &Result[0], Size);

	if (0 == Size)
	{
		MSGASSERT("MultiByteToWideChar ���ڿ� ��ȯ�� �����߽��ϴ�" + std::string(Str));
		return L"";
	}

	return Result;
}


