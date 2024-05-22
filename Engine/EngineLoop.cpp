#include "EngineLoop.h"

ENGINE_API UEngine* GEngine = nullptr;

FEngineLoop::~FEngineLoop()
{
}

int32 FEngineLoop::PreInit(const char* CmdLine)
{
	PRINT_FUNCTION_NAME();
	for (auto& It : MapClass)
	{
		It.second->CreateDefaultObject();
	}

	return int32();
}

int32 FEngineLoop::Init()
{
	PRINT_FUNCTION_NAME();
	Engine = NewObject<UEngine>(nullptr);
	GEngine = Engine.get();
	GEngine->Init();
	GEngine->Start();

	return 0;
}

void FEngineLoop::Tick()
{
	 GEngine->Tick(1.0f);
	 std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void FEngineLoop::Exit()
{
	PRINT_FUNCTION_NAME();
	if (GEngine)
	{
		GEngine->Exit();
		GEngine = nullptr;
		Engine = nullptr;
	}

	for (auto& It : MapClass)
	{
		if (UObject* CDO = It.second->GetDefaultObject())
		{
			CDO->__DefaultDestructor();
			GUObjectArray.Free(It.second->ClassTypeInfo, CDO);
		}
		It.second->~UClass();
		GUObjectArray.Free(typeid(UClass), It.second);
	}
	MapClass.clear();
	GUObjectArray.Destroy();
}
