#include "..\Core\CoreMinimal.h"

int32 LAUNCH_API GuardedMain(const char* CmdLine);

int32 main()
{
	PRINT_FUNCTION_NAME();
	int32 Result = GuardedMain(nullptr);

	return Result;
}