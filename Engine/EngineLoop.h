#pragma once

#include "..\Core\CoreMinimal.h"
#include "..\Core\ObjectGlobals.h"
#include "Engine.h"

class ENGINE_API FEngineLoop
{
public:
	FEngineLoop() {}

	virtual ~FEngineLoop();

	int32 PreInit(const char* CmdLine);
	int32 Init();
	void Tick();

	void Exit();
	

private:
	shared_ptr<UEngine> Engine;
};

