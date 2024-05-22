#include "Object.h"

UObject::UObject()
{
}

UObject::UObject(const FObjectInitializer& ObjectInitializer)
{
	const_cast<FObjectInitializer&>(ObjectInitializer).Obj = this;
}

FObjectInitializer& FObjectInitializer::Get()
{
	static FObjectInitializer Default;
	return Default;
}

FObjectInitializer::FObjectInitializer(const EObjectFlags InObjectFlags)
	:ObjectFlags(InObjectFlags)
{}

FObjectInitializer::FObjectInitializer(const FStaticConstructObjectParameters& InStaticConstructObjectParameters)
	: Class (InStaticConstructObjectParameters.Class)
	, OuterPrivate (InStaticConstructObjectParameters.Outer)
	, ObjectFlags (InStaticConstructObjectParameters.SetFlags)
	, Name (InStaticConstructObjectParameters.Name)
{}

UObjectBase::UObjectBase(UClass* InClass, EObjectFlags InFlags, UObject* InOuter)
	: ObjectFlags (InFlags)
	, OuterPrivate (InOuter)
	, Class (InClass)
{}
