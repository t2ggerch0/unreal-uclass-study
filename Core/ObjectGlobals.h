#pragma once
#include "CoreMinimal.h"
#include "ObjectMacros.h"

class UClass;
class UObject;

struct CORE_API FStaticConstructObjectParameters
{
	UClass* Class = nullptr;
	UObject* Outer = nullptr;

	wstring Name;

	EObjectFlags SetFlags = RF_NoFlags;

	FStaticConstructObjectParameters(UClass* InClass);
};

CORE_API shared_ptr<UObject> StaticConstructObject_Internal(FStaticConstructObjectParameters& Params);

template<class T>
shared_ptr<T> NewObject(UObject* Outer, UClass* Class = nullptr, wstring Name = NAME_NONE, EObjectFlags Flags = RF_NoFlags)
{
	PRINT_FUNCTION_NAME();
	if (!Class)
	{
		Class = T::StaticClass();
	}

	FStaticConstructObjectParameters Params(Class);
	Params.Outer = Outer;
	Params.Name = Name;
	Params.SetFlags = Flags;
	return Cast<T> (StaticConstructObject_Internal(Params));
}