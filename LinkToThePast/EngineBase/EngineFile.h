#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>

#include "EnginePath.h"

// ���ϰ� ���õ� ��� ����� ���⿡�� ����մϴ�.
// FIle ����
// �ڵ� ���ʿ� �߸�����ϱ⵵ ����� ¥�°��� ����Ʈ �Դϴ�.
// ����
// �̵�


const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
	// �ϵ��ڵ� 
public:
	UEngineFile();
	// ����ü��
	UEngineFile(std::string_view _Path);
	UEngineFile(std::filesystem::path _Path);
	~UEngineFile();

	// Write
	void Write(const void* _Ptr, size_t _Size);
	void Read(void* _Ptr, size_t _Size);

	void FileOpen(const char* _Mode);
	bool IsExits();
	void Close();

	// ��� Ŭ���� ����
private:
	// ���
	// _MAX_DIR �����쿡 �������� ���α׷�


	char Path[MAXPATH] = "";
	FILE* File = nullptr;
};

