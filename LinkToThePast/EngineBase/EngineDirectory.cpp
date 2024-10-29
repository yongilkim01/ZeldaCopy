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
	/** ����� ��ȯ�� ���� ��ü */
	std::vector<class UEngineFile> Result;

	/** ���丮 �� �׸��� ��ȸ�ϴ� ���ͷ����� Ÿ�� ������ ���ؼ� ������ ���丮 ���� � ���� ���� �ִ����� �˻� */ 
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	/** ���丮 �� �׸��� ��ȸ */
	while (false == Diriter._At_end())
	{
		// ���� ��θ� ���ο� ������ �Ҵ�
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
	// ��θ� �־��ָ� �� ����� ù��° ������ ����Ű�� �ȴ�.
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