#pragma once
#include <filesystem>

/**
 * 파일 경로 래핑 클래스
 */
class UEnginePath
{
public:
	/** 생성자, 소멸자 */
	UEnginePath();
	UEnginePath(std::string_view FilePath);
	UEnginePath(std::filesystem::path FilePath);
	~UEnginePath();

	/** 디렉토리 상위 디렉토리로 이동하는 메소드 */
	void MoveParent();
	/** 특정 디렉토리가 나올 때 까지 UEnginePath::MoveParent를 호출하는 메소드 */
	bool MoveParentToDirectory(std::string_view FilePath);
	void Append(std::string_view AppendName);

	bool IsDirectory();
	bool IsFile();
	bool IsExists();

	/** 파일경로를 반환하는 메소드 */
	std::string GetPathToString();
	/** 파일명 + 확장자 포함을 반환하는 메소드 */
	std::string GetFileName();
	/** 파일명 + 확장자 포함을 반환하는 메소드 */
	std::string GetDirectoryName();
	/** 확장자를 반환하는 메소드 */
	std::string GetExtension();


protected:
	std::filesystem::path Path;

private:
};

