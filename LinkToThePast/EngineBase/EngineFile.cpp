#include "PreCompile.h"
#include "EngineFile.h"
#include "EngineDebug.h"
#include "EngineSerializer.h"

UEngineFile::UEngineFile()
{


}

UEngineFile::UEngineFile(const std::string& Path)
	: UEnginePath(std::string_view(Path.c_str()))
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
	fopen_s(&File, GetPathToString().c_str(), Mode);

	if (nullptr == File)
	{
		MSGASSERT(GetPathToString() + +"���� ���¿� �����߽��ϴ�");
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

void UEngineFile::Write(UEngineSerializer& Ser)
{
	Write(Ser.GetDataPtr(), Ser.GetWriteOffset());
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

void UEngineFile::Read(UEngineSerializer& Ser)
{
	int FileSize = GetFileSize();

	Ser.DataResize(FileSize);

	Read(Ser.GetDataPtr(), FileSize);
}

void UEngineFile::Close()
{
	if (nullptr != File)
	{
		fclose(File);
		File = nullptr;
	}
}

int UEngineFile::GetFileSize()
{
	if (false == IsFile())
	{
		MSGASSERT(Path.string() + "������ �ƴ� ������ ũ�⸦ �˼��� �����ϴ�.");
		return -1;
	}

	return static_cast<int>(std::filesystem::file_size(Path));
}

