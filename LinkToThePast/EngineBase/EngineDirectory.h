#pragma once
#include <vector>
// �ֽ� std����� �̿��غ��̴ϴ�.
#include "EnginePath.h"

// ���а� ���°� �����е��� ���幮��.

// ���� : 
class UEngineDirectory : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineDirectory();
	UEngineDirectory(std::string_view _Path);
	UEngineDirectory(std::filesystem::path _Path);
	~UEngineDirectory();

	//// delete Function
	//UEngineDirectory(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	//UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

	// �ð��� �ʹ� ���ٰ� �ȸ���. ���߿� ��������.
	std::vector<class UEngineFile> GetAllFile(bool _IsRecursive = true);

	std::vector<class UEngineDirectory> GetAllDirectory();

protected:

private:
	void GetAllFileRecursive(std::filesystem::path _Path, std::vector<class UEngineFile>& _Result);

};

