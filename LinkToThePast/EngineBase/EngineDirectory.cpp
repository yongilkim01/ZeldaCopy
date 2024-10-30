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

UEngineDirectory::~UEngineDirectory()
{

}

std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool IsRecursive /* = true */)
{
	// ����� ��ȯ�� ���� ��ü
	std::vector<class UEngineFile> Result;

	// ���丮 �� �׸��� ��ȸ�ϴ� ���ͷ����� Ÿ�� ������ ���ؼ� ������ ���丮 ���� � ���� ���� �ִ����� �˻�
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	// ���丮 �� �׸��� ��ȸ
	while (Diriter._At_end() == false)
	{
		// ���� ��θ� ���ο� ������ �Ҵ�
		std::filesystem::path FilePath = *Diriter;

		// ���� ��θ� ���ؼ� UEnginePath ��ü ����
		UEnginePath Path = UEnginePath(FilePath);

		// ���� ����� ���丮�� ��ȿ�� ���
		if (Path.IsDirectory() == true)
		{
			// IsRecursive�� true�� ���
			if (IsRecursive == true)
			{
				GetAllFileRecursive(FilePath, Result);
			}

			++Diriter;
			continue;
		}

		// ��� ���Ϳ� �߰�
		Result.push_back(UEngineFile(FilePath));
		// ��ȯ�� ���ؼ� ���ͷ����� �߰�
		++Diriter;
	}
	// ��� ���� ��ȯ
	return Result;
}

void UEngineDirectory::GetAllFileRecursive(std::filesystem::path _Path, std::vector<class UEngineFile>& Result)
{
	// ��θ� �־��ָ� �� ����� ù��° ������ ��Ŀ��
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(_Path);

	// ��ȸ�� ���� �ݺ���
	while (Diriter._At_end() == false)
	{
		// ���� ���� ��θ� ������ �Ҵ�
		std::filesystem::path FilePath = *Diriter;

		// ���� ��θ� ���ؼ� UEnginePath ��ü ����
		UEnginePath Path = UEnginePath(FilePath);

		// ���� ����� ���丮�� ��ȿ�� ���
		if (Path.IsDirectory() == true)
		{
			GetAllFileRecursive(FilePath, Result);
			++Diriter;
			continue;
		}
		
		// ��� �迭�� �߰�
		Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}
}