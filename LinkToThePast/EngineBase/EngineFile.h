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
	/** ������, �Ҹ��� */
	UEngineFile();
	UEngineFile(const std::string& Path);
	UEngineFile(std::string_view Path);
	UEngineFile(std::filesystem::path Path);
	~UEngineFile();

	/** ���� ���� �б� �޼ҵ� */
	void Write(const void* Ptr, size_t Size);
	void Write(UEngineSerializer& Ser);
	void Read(void* Ptr, size_t Size);
	void Read(UEngineSerializer& Ser);

	/** ���� ���� �ݱ� �޼ҵ� */
	void FileOpen(const char* Mode);
	void Close();
	int GetFileSize();

private:
	FILE* File = nullptr;
};

