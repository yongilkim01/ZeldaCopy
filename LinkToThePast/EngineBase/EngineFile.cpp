#include "PreCompile.h"
#include "EngineFile.h"
#include "EngineDebug.h"

UEngineFile::UEngineFile()
{


}

UEngineFile::UEngineFile(std::string_view Path)
	: UEnginePath(Path)
{

}

UEngineFile::UEngineFile(std::filesystem::path Path)
	: UEnginePath(Path)
{

}

UEngineFile::~UEngineFile()
{
	Close();
}

void UEngineFile::FileOpen(const char* Mode)
{
	fopen_s(&File, Path, Mode);

	// ������ ���� ���Ͽ��� �� ���α׷� ����
	if (nullptr == File)
	{
		MSGASSERT(Path /*+ "���� ���¿� �����߽��ϴ�"*/);
	}
}


void UEngineFile::Write(const void* Ptr, size_t Size)
{
	if (0 == Size)
	{
		MSGASSERT("ũ�Ⱑ 0�� �����͸� ������ �����ϴ�.");
	}

	if (nullptr == Ptr)
	{
		MSGASSERT("�������� �ʴ� �޸𸮸� ����Ϸ��� �߽��ϴ�.");
	}

	// w�� ��쿡 ���� ����ó��
	if (nullptr == File)
	{
		MSGASSERT("���� ���� ���Ͽ� ������ ������ �߽��ϴ�");
		return;
	}

	fwrite(Ptr, Size, 1, File);
}

void UEngineFile::Read(void* Ptr, size_t Size)
{
	if (0 == Size)
	{
		MSGASSERT("ũ�Ⱑ 0�� �����͸� �������� �����ϴ�.");
	}

	if (nullptr == Ptr)
	{
		MSGASSERT("�������� �ʴ� �޸𸮸� �������� �߽��ϴ�.");
	}

	if (nullptr == File)
	{
		MSGASSERT("���� ���� ���Ͽ� ������ ������ �߽��ϴ�");
		return;
	}

	fread(Ptr, Size, 1, File);
}

bool UEngineFile::IsExits()
{
	int Result = _access(Path, 00);

	// 0�̸� �ִ°� 0 �̿��� ���̸� ���� ��
	return 0 == Result;
}

void UEngineFile::Close()
{
	if (nullptr != File)
	{
		fclose(File);
		File = nullptr;
	}
}

