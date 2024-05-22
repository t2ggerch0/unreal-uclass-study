#pragma once

#include <string>
#include <filesystem>
#include <windows.h>
using namespace std;

class CORE_API FPaths
{
public:
	// 엔진 폴더, ini 폴더, 유저 dll 폴더
	static const wstring& EngineDir();
	static const wstring& EngineConfigDir();
	static const wstring& ProjectDllDir();
};

