#include "Paths.h"


const wstring& FPaths::EngineDir()
{
	static const wstring Path = filesystem::current_path();
	return Path;
}

const wstring& FPaths::EngineConfigDir()
{
	static const wstring Path = EngineDir() + TEXT("\\config");
	return Path;
}

const wstring& FPaths::ProjectDllDir()
{
	static const wstring Path = EngineDir() + TEXT("\\project");
	return Path;
}