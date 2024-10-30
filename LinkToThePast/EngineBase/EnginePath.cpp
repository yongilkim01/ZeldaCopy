#include "PreCompile.h"
#include "EnginePath.h"
#include "EngineDebug.h"

UEnginePath::UEnginePath()
	: Path(std::filesystem::current_path())
{
}

UEnginePath::UEnginePath(std::string_view _Path)
	: Path(_Path)
{
}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

UEnginePath::~UEnginePath()
{
}

bool UEnginePath::IsExists()
{
	// ��ΰ� ��ȿ���� Ȯ��
	return std::filesystem::exists(Path);
}

bool UEnginePath::IsDirectory()
{
	// ��ΰ� ��ȿ���� Ȯ��
	return std::filesystem::is_directory(Path);
}

bool UEnginePath::IsFile()
{
	return IsDirectory() == false;
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

std::string UEnginePath::GetPathToString()
{
	return Path.string();
}

std::string UEnginePath::GetFileName()
{
	return Path.filename().string();
}

std::string UEnginePath::GetExtension()
{
	return Path.extension().string();
}

bool UEnginePath::MoveParentToDirectory(std::string_view _Path)
{
	UEnginePath DummyPath = UEnginePath(Path);

	if (DummyPath.IsDirectory() == false)
	{
		MSGASSERT("���丮 ����϶��� MoveParentToDirectory �� ȣ���Ҽ� �ֽ��ϴ�");
		return false;
	}

	bool Result = false;
	std::filesystem::path CurPath = DummyPath.Path;

	while (CurPath != CurPath.root_path())
	{
		CurPath = DummyPath.Path;
		CurPath.append(_Path);

		if (true == std::filesystem::exists(CurPath))
		{
			Result = true;
			Path = CurPath;
			break;
		}
		DummyPath.MoveParent();
	}

	return Result;
}
