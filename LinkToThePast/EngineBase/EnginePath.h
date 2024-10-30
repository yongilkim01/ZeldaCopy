#pragma once
#include <filesystem>

/**
* 파일 불러오기를 위한 클래스
*/
class UEnginePath
{
public:
	/** 생성자 소멸자 */
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	/** 상위 디렉토리로 이동하는 메소드 */
	void MoveParent();
	/** 상위 디렉토리로 이동하는 메소드 */
	bool MoveParentToDirectory(std::string_view _Path);
	/** 경로를 String 객체로 반환하는 메소드 */
	std::string GetPathToString();
	/** 파일명 + 확장자 반환하는 메소드 */
	std::string GetFileName();
	/** 확장자 메소드 */
	std::string GetExtension();

	/** 경로상의 디렉토리 또는 파일이 유효한지 확인하는 메소드 */
	bool IsExists();
	/** 디렉토리가 유효한지 확인하는 메소드 */
	bool IsDirectory();
	/** 파일이 유효한지 확인하는 메소드 */
	bool IsFile();

protected:
	/** 경로상를 담는 멤버 변수 */
	std::filesystem::path Path;

private:

};

