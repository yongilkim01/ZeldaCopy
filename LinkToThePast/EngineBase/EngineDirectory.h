#pragma once
#include "EnginePath.h"

#include <vector>

/**
 * ���丮 ���� ��ȸ Ŭ����
 */
class UEngineDirectory : public UEnginePath
{
public:
	/** ������, �Ҹ��� */
	UEngineDirectory();
	UEngineDirectory(std::string_view InitPath);
	UEngineDirectory(std::filesystem::path InitPath);
	~UEngineDirectory();

	/** 
	 * ���丮 �� ��� ���ϵ��� �����ͼ� UEngineFile Ÿ������ ���� ���� �� ��ȯ�ϴ� �޼ҵ�

	 * @param IsRecursive - ��͸� ���� ���丮 ��ȸ ����
	 */
	std::vector<class UEngineFile> GetAllFile(bool IsRecursive = true);

	/** ���丮 �� ��� ���丮���� �����ͼ� UEngineDirectory Ÿ������ ���� ���� �� ��ȯ�ϴ� �޼ҵ� */
	std::vector<class UEngineDirectory> GetAllDirectory();

protected:

private:
	/** 
	 * ���丮 �� ��� ���ϵ��� ��� �������� �������� �޼ҵ�, UEngineDirectory::GetAllFile���� IsRecursive�� true�� �����Ͽ��� �� ȣ��
	 *
	 * @param Path - ���丮 ���
	 * @param Result - ��� ���� ������ ������ ���� ��ü
	 */
	void GetAllFileRecursive(std::filesystem::path Path, std::vector<class UEngineFile>& Result);
};

