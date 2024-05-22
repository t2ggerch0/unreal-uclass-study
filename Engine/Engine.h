#pragma once
#include "..\Core\CoreMinimal.h"

#include "..\Core\Object.h"
#include "..\Core\ObjectGlobals.h"
#include "..\Core\ObjectArray.h"
#include "..\Core\ObjectMacros.h"
#include "..\Core\Class.h"

#include "Engine.generated.h"

UCLASS()
class ENGINE_API UEngine : public UObject
{
	GENERATED_BODY()
public:
	UEngine();

public:
	void Init();
	void Start();
	void Tick(float DeltaSeconds);
	void Exit();

};

extern ENGINE_API class UEngine* GEngine;
