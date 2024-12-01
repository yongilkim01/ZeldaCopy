#include "PreCompile.h"
#include "EnginePath.h"
#include "EngineDebug.h"

UEnginePath::UEnginePath()
	: Path(std::filesystem::current_path())
{
}

UEnginePath::UEnginePath(std::string_view FilePath)
	: Path(FilePath)
{

}

UEnginePath::UEnginePath(std::filesystem::path FilePath)
	: Path(FilePath)
{

}

UEnginePath::~UEnginePath()
{
}

std::string UEnginePath::GetPathToString()
{
	return Path.string();
}

std::string UEnginePath::GetFileName()
{
	if (true == IsDirectory())
	{
		MSGASSERT("���� ��� �϶��� GetFileName�� ȣ���Ҽ� �ֽ��ϴ�." + Path.string());
		return "";
	}

	return Path.filename().string();
}

std::string UEnginePath::GetDirectoryName()
{
	if (false == IsDirectory())
	{
		MSGASSERT("���丮 ��� �϶��� GetDirectoryName�� ȣ���Ҽ� �ֽ��ϴ�." + Path.string());
		return "";
	}

	return Path.filename().string();
}

std::string UEnginePath::GetExtension()
{
	return Path.extension().string();
}


bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

bool UEnginePath::IsFile()
{
	return false == IsDirectory();
}

bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void UEnginePath::Append(std::string_view AppendName)
{
	Path.append(AppendName);
}

bool UEnginePath::MoveParentToDirectory(std::string_view FilePath)
{
	UEnginePath DummyPath = UEnginePath(Path);

	if (false == DummyPath.IsDirectory())
	{
		MSGASSERT("���丮 ����϶��� MoveParentToDirectory �� ȣ���Ҽ� �ֽ��ϴ�");
		return false;
	}

	bool Result = false;
	std::filesystem::path CurPath = DummyPath.Path;

	std::filesystem::path Root = CurPath.root_path();
	while (true)
	{
		CurPath = DummyPath.Path;

		if (CurPath == Root)
		{
			break;
		}

		CurPath.append(FilePath);
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



