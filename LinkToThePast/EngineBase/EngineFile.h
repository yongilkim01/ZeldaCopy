#pragma once
/** Std Header */
#include <Windows.h>
#include <iostream>
#include <io.h>

/** Engine Header */
#include "EnginePath.h"


const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
public:
	/** 생성자, 소멸자 */
	UEngineFile();
	UEngineFile(std::string_view Path);
	UEngineFile(std::filesystem::path Path);
	~UEngineFile();

	/** 파일 쓰기 읽기 메소드 */
	void Write(const void* Ptr, size_t Size);
	void Read(void* Ptr, size_t Size);

	/** 파일 열고 닫기 메소드 */
	void FileOpen(const char* Mode);
	bool IsExits();
	void Close();

private:
	char Path[MAXPATH] = "";
	FILE* File = nullptr;
};

