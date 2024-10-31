#pragma once
#include <filesystem>

// ���� :
class UEnginePath
{
public:
	// constrcuter destructer
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	//// delete Function
	//UEnginePath(const UEnginePath& _Other) = delete;
	//UEnginePath(UEnginePath&& _Other) noexcept = delete;
	//UEnginePath& operator=(const UEnginePath& _Other) = delete;
	//UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;

	bool IsExists();
	void MoveParent();

	std::string GetPathToString();

	// ���ϸ� + Ȯ���� ����
	std::string GetFileName();

	// ���ϸ� + Ȯ���� ����
	std::string GetDirectoryName();

	// Ȯ����
	std::string GetExtension();


	// "C:\\AAAA\\BBBB\\";
	// "C:\\AAAA\\BBBB\\Resources";
	// "C:\\AAAA\\"
	// "C:\\AAAA\\Resources"
	// "C:\\"
	// "C:\\Resources"
	// Ư�� ���丮�� ���ö����� MoveParent�� �ݺ��ϴ� �Լ�.
	bool MoveParentToDirectory(std::string_view _Path);

	bool IsDirectory();

	bool IsFile();

	void Append(std::string_view _AppendName);


protected:
	std::filesystem::path Path;

private:
};

