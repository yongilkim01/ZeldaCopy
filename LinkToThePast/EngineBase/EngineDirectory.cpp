#include "PreCompile.h"
#include "EngineDirectory.h"
#include "EngineFile.h"

UEngineDirectory::UEngineDirectory()
	: UEnginePath()
{

}

UEngineDirectory::UEngineDirectory(std::string_view _Path)
	: UEnginePath(_Path)
{
}

UEngineDirectory::~UEngineDirectory()
{

}

std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecursive /** = true */)
{
	/** 결과를 반환할 벡터 객체 */
	std::vector<class UEngineFile> Result;

	/** 디렉토리 내 항목을 순회하는 이터레이터 타입 변수를 통해서 지정된 디렉토리 내에 어떤 파일 들이 있는지를 검사 */ 
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	/** 디렉토리 내 항목을 순회 */
	while (false == Diriter._At_end())
	{
		// 현재 경로를 새로운 변수에 할당
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			if (true == _IsRecursive)
			{
				GetAllFileRecursive(FilePath, Result);
			}

			++Diriter;
			continue;
		}

		Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}

	return Result;
}



void UEngineDirectory::GetAllFileRecursive(std::filesystem::path _Path
	, std::vector<class UEngineFile>& _Result)
{
	// 경로를 넣어주면 그 경로의 첫번째 파일을 가리키게 된다.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(_Path);

	while (false == Diriter._At_end())
	{
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			GetAllFileRecursive(FilePath, _Result);
			++Diriter;
			continue;
		}

		_Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}
}