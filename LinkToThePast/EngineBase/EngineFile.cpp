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
		MSGASSERT(GetPathToString() + +"파일 오픈에 실패했습니다");
	}
}


void UEngineFile::Write(const void* Ptr, size_t Size)
{
	if (0 == Size)
	{
		MSGASSERT("크기가 0인 데이터를 쓸수는 없습니다.");
	}

	if (nullptr == Ptr)
	{
		MSGASSERT("존재하지 않는 메모리를 사용하려고 했습니다.");
	}

	// w일 경우에 대한 예외처리
	if (nullptr == File)
	{
		MSGASSERT("열지 않은 파일에 내용을 쓰려고 했습니다");
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
		MSGASSERT("크기가 0인 데이터를 읽을수는 없습니다.");
	}

	if (nullptr == Ptr)
	{
		MSGASSERT("존재하지 않는 메모리를 읽으려고 했습니다.");
	}

	if (nullptr == File)
	{
		MSGASSERT("열지 않은 파일에 내용을 쓰려고 했습니다");
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
		MSGASSERT(Path.string() + "파일이 아닌 존재의 크기를 알수는 없습니다.");
		return -1;
	}

	return static_cast<int>(std::filesystem::file_size(Path));
}

