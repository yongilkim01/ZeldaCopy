#include "PreCompile.h"
#include "EngineDirectory.h"
#include "EngineFile.h"

UEngineDirectory::UEngineDirectory()
	: UEnginePath()
{

}

UEngineDirectory::UEngineDirectory(std::string_view Path)
	: UEnginePath(Path)
{
}

UEngineDirectory::UEngineDirectory(std::filesystem::path _Path)
	: UEnginePath(_Path)
{
}

UEngineDirectory::~UEngineDirectory()
{

}

std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool IsRecursive /* = true */)
{
	// 결과를 반환할 벡터 객체
	std::vector<class UEngineFile> Result;

	// 디렉토리 내 항목을 순회하는 이터레이터 타입 변수를 통해서 지정된 디렉토리 내에 어떤 파일 들이 있는지를 검사
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	// 디렉토리 내 항목을 순회
	while (Diriter._At_end() == false)
	{
		// 현재 경로를 새로운 변수에 할당
		std::filesystem::path FilePath = *Diriter;

		// 파일 경로를 통해서 UEnginePath 객체 생성
		UEnginePath Path = UEnginePath(FilePath);

		// 파일 경로의 디렉토리가 유효할 경우
		if (Path.IsDirectory() == true)
		{
			// IsRecursive가 true일 경우
			if (IsRecursive == true)
			{
				GetAllFileRecursive(FilePath, Result);
			}

			++Diriter;
			continue;
		}

		// 결과 벡터에 추가
		Result.push_back(UEngineFile(FilePath));
		// 순환을 위해서 이터레이터 추가
		++Diriter;
	}
	// 결과 벡터 반환
	return Result;
}

std::vector<class UEngineDirectory> UEngineDirectory::GetAllDirectory()
{
	// 결과를 반환할 벡터 객체
	std::vector<class UEngineDirectory> Result;

	// 경로를 넣어주면 그 경로의 첫번째 파일을 가리키게 된다.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	while (Diriter._At_end() == false)
	{
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);

		if (Path.IsDirectory() == false)
		{
			++Diriter;
			continue;
		}

		Result.push_back(UEngineDirectory(FilePath));
		++Diriter;
	}

	return Result;
}

void UEngineDirectory::GetAllFileRecursive(std::filesystem::path Path, std::vector<class UEngineFile>& Result)
{
	// Path의 첫번째 파일 또는 디렉토리를 포커스
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	// 순회를 위한 반복문
	while (Diriter._At_end() == false)
	{
		// 현재 파일 경로를 변수에 할당
		std::filesystem::path FilePath = *Diriter;

		// 파일 경로를 통해서 UEnginePath 객체 생성
		UEnginePath Path = UEnginePath(FilePath);

		// 파일 경로의 디렉토리가 유효할 경우
		if (Path.IsDirectory() == true)
		{
			GetAllFileRecursive(FilePath, Result);
			++Diriter;
			continue;
		}
		
		// 결과 배열의 추가
		Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}
}