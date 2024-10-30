#pragma once
#include <filesystem>

/**
* ���� �ҷ����⸦ ���� Ŭ����
*/
class UEnginePath
{
public:
	/** ������ �Ҹ��� */
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	/** ���� ���丮�� �̵��ϴ� �޼ҵ� */
	void MoveParent();
	/** ���� ���丮�� �̵��ϴ� �޼ҵ� */
	bool MoveParentToDirectory(std::string_view _Path);
	/** ��θ� String ��ü�� ��ȯ�ϴ� �޼ҵ� */
	std::string GetPathToString();
	/** ���ϸ� + Ȯ���� ��ȯ�ϴ� �޼ҵ� */
	std::string GetFileName();
	/** Ȯ���� �޼ҵ� */
	std::string GetExtension();

	/** ��λ��� ���丮 �Ǵ� ������ ��ȿ���� Ȯ���ϴ� �޼ҵ� */
	bool IsExists();
	/** ���丮�� ��ȿ���� Ȯ���ϴ� �޼ҵ� */
	bool IsDirectory();
	/** ������ ��ȿ���� Ȯ���ϴ� �޼ҵ� */
	bool IsFile();

protected:
	/** ��λ� ��� ��� ���� */
	std::filesystem::path Path;

private:

};

