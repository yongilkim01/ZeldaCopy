#pragma once
/** Std Header file */
#include <filesystem>

/**
 * ���� ��θ� ������ Ŭ����
 */
class UEnginePath
{
public:
	/** ������, �Ҹ��� */
	UEnginePath();
	UEnginePath(std::string_view FilePath);
	UEnginePath(std::filesystem::path FilePath);
	~UEnginePath();

	/** ��ü �� ���� ���� */
	//UEnginePath(const UEnginePath& _Other) = delete;
	//UEnginePath(UEnginePath&& _Other) noexcept = delete;
	//UEnginePath& operator=(const UEnginePath& _Other) = delete;
	//UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;

	// "C:\\AAAA\\BBBB\\";
	// "C:\\AAAA\\BBBB\\Resources";
	// "C:\\AAAA\\"
	// "C:\\AAAA\\Resources"
	// "C:\\"
	// "C:\\Resources"
	/** ���丮 ���� ���丮�� �̵��ϴ� �޼ҵ� */
	void MoveParent();
	/** Ư�� ���丮�� ���� �� ���� UEnginePath::MoveParent�� ȣ���ϴ� �޼ҵ� */
	bool MoveParentToDirectory(std::string_view FilePath);
	void Append(std::string_view AppendName);

	bool IsDirectory();
	bool IsFile();
	bool IsExists();

	/** ���ϰ�θ� ��ȯ�ϴ� �޼ҵ� */
	std::string GetPathToString();
	/** ���ϸ� + Ȯ���� ������ ��ȯ�ϴ� �޼ҵ� */
	std::string GetFileName();
	/** ���ϸ� + Ȯ���� ������ ��ȯ�ϴ� �޼ҵ� */
	std::string GetDirectoryName();
	/** Ȯ���ڸ� ��ȯ�ϴ� �޼ҵ� */
	std::string GetExtension();


protected:
	std::filesystem::path Path;

private:
};

