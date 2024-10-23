#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>

// ���ϰ� ���õ� ��� ����� ���⿡�� ����մϴ�.
// FIle ����
// �ڵ� ���ʿ� �߸�����ϱ⵵ ����� ¥�°��� ����Ʈ �Դϴ�.
// ����
// �̵�


const int MAXPATH = 256;

class UEngineFile
{
	// �ϵ��ڵ� 
public:
	UEngineFile();
	~UEngineFile();

	inline void SetPath(const char* _Path)
	{
		strcpy_s(Path, _Path);
	}

	// �׷��ž� Is 
	// Path ��ο� ������ ������? �������� �����ϴ� �ž�?

	// ������ �Լ����� ��쿡�� �и�����
	// �Լ� �ϳ��� ��µ�?
	// ����� ������ �и��ϸ� inline�� ������ ���Ѵ�.

	// 1. if for������ ������ �ٸ� ����� �Ȼ���ϸ� ���� inline���� ������� 
	// 2. �׷��� �ʹ� ��� �����ϸ� �ȸ���ϴ� inline���� 
	// 3. �������� �ܺ��Լ��� ����� ���ٸ� ���� �ϳ��� inline�� ���ٸ� inline���� �ȸ����.

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

