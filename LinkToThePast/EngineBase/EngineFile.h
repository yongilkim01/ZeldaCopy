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
	/** ������, �Ҹ��� */
	UEngineFile();
	UEngineFile(std::string_view Path);
	UEngineFile(std::filesystem::path Path);
	~UEngineFile();

	/** ���� ���� �б� �޼ҵ� */
	void Write(const void* Ptr, size_t Size);
	void Read(void* Ptr, size_t Size);

	/** ���� ���� �ݱ� �޼ҵ� */
	void FileOpen(const char* Mode);
	bool IsExits();
	void Close();

private:
	char Path[MAXPATH] = "";
	FILE* File = nullptr;
};

