#pragma once
#include "CoreMinimal.h"
#include "ObjectGlobals.h"

class UClass;
class UObject;

struct CORE_API FObjectInitializer
{
	UClass* Class = nullptr;
	EObjectFlags ObjectFlags = EObjectFlags::RF_NoFlags;

	UObject* OuterPrivate = nullptr;
	UObject* Obj = nullptr;

	std::shared_ptr<UObject> ResultSharedPointer;

	wstring Name;

	UObject* GetObj() const { return Obj; }

	static FObjectInitializer& Get();

	FObjectInitializer(){}
	FObjectInitializer(const EObjectFlags InObjectFlags);
	FObjectInitializer(const FStaticConstructObjectParameters& InStaticConstructObjectParameters);
};

#pragma warning(disable:26495)
class CORE_API UObjectBase : public enable_shared_from_this<UObjectBase>
{
public:
	UObjectBase(){}
	UObjectBase(UClass* InClass, EObjectFlags InFlags, UObject* InOuter);
	virtual ~UObjectBase(){}

	UClass* GetClass()const { return Class; }
	EObjectFlags GetFlags() const { return ObjectFlags; }
	UObject* GetOuter() const { return OuterPrivate; }

protected:
	EObjectFlags ObjectFlags;
	UObject* OuterPrivate;
	UClass* Class;
};
#pragma warning(default:26495)

class CORE_API UObject : public UObjectBase
{
public:
	UObject();
	UObject(const FObjectInitializer& ObjectInitializer);

	static UClass* StaticClass() { return nullptr; }
	virtual void __DefaultDestructor() { this->~UObject(); }

	bool HasAnyFlags(const EObjectFlags FlagToCheck) const
	{
		return (GetFlags() & FlagToCheck) != 0;
	}

	const wstring& GetName() const { return Name; }
	wstring Name;
};

template<class T, class T2>
static shared_ptr<T> Cast(shared_ptr<T2> InObj) { return reinterpret_pointer_cast<T>( InObj ); }
