#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>

#include "EnginePath.h"

class UEngineSerializer;

const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
public:
	/** 생성자, 소멸자 */
	UEngineFile();
	UEngineFile(const std::string& Path);
	UEngineFile(std::string_view Path);
	UEngineFile(std::filesystem::path Path);
	~UEngineFile();

	/** 파일 쓰기 읽기 메소드 */
	void Write(const void* Ptr, size_t Size);
	void Write(UEngineSerializer& Ser);
	void Read(void* Ptr, size_t Size);
	void Read(UEngineSerializer& Ser);

	/** 파일 열고 닫기 메소드 */
	void FileOpen(const char* Mode);
	void Close();
	int GetFileSize();

private:
	FILE* File = nullptr;
};

