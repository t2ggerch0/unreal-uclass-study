#include "..\Core\CoreMinimal.h"
#include "..\Engine\EngineLoop.h"

FEngineLoop GEngineLoop;

int32 EnginePreInit(const char* CmdLine)
{
	const int32 ErrorLevel = GEngineLoop.PreInit(CmdLine);
	return ErrorLevel;
}

int32 EngineInit()
{
	const int32 ErrorLevel = GEngineLoop.Init();
	return ErrorLevel;
}

void EngineTick()
{
	GEngineLoop.Tick();
}

void EngineExit()
{
	GEngineLoop.Exit();
}

int32 LAUNCH_API GuardedMain(const char* CmdLine)
{
	int32 ErrorLevel = EnginePreInit(CmdLine);

	if (ErrorLevel != 0)
	{
		return ErrorLevel;
	}

	ErrorLevel = EngineInit();
	if (ErrorLevel != 0)
	{
		return ErrorLevel;
	}

	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
		EngineTick();
	}

	EngineExit();

	return ErrorLevel;
}
