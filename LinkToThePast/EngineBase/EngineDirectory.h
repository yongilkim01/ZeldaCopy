#pragma once
/** Engine Header */
#include "EnginePath.h"

/** Std Header */
#include <vector>

/**
 * ���丮 ���� ��ȸ ����� �ϴ� Ŭ����
 */
class UEngineDirectory : public UEnginePath
{
public:
	/** ������, �Ҹ��� */
	UEngineDirectory();
	UEngineDirectory(std::string_view _Path);
	UEngineDirectory(std::filesystem::path _Path);
	~UEngineDirectory();

	/** ��ü �� ���� ���� */
	//UEngineDirectory(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	//UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

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

