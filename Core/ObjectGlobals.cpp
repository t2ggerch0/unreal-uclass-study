#include "ObjectGlobals.h"
#include "Class.h"

FStaticConstructObjectParameters::FStaticConstructObjectParameters(UClass* InClass)
	: Class (InClass)
{}

CORE_API shared_ptr<UObject> StaticConstructObject_Internal(FStaticConstructObjectParameters& Params)
{
	UClass* InClass = Params.Class;
	wstring& InName = Params.Name;

	if (InName == NAME_NONE)
	{
		static std::map<wstring_view, int64> NameTable;
		wstring ClassName = InClass->ClassName.data();
		int64& NewIndex = NameTable[InClass->ClassName];
		InName = ClassName + TEXT("_") + to_wstring(NewIndex);
		++NewIndex;
	}

	FObjectInitializer ObjectInitializer{Params};
	if (ObjectInitializer.ObjectFlags & EObjectFlags::RF_ClassDefaultObject)
	{
		_ASSERT(false);
	}

	InClass->ClassConstructor(ObjectInitializer);
	ObjectInitializer.Obj->Name = ObjectInitializer.Name;
	return ObjectInitializer.ResultSharedPointer;
}
