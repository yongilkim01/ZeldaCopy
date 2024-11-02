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

	// 파일을 열지 못하였을 때 프로그램 종료
	if (nullptr == File)
	{
		MSGASSERT(Path /*+ "파일 오픈에 실패했습니다"*/);
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

bool UEngineFile::IsExits()
{
	int Result = _access(Path, 00);

	// 0이면 있는것 0 이외의 값이면 없는 것
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

