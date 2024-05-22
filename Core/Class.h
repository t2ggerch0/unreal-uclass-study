#pragma once
#include "Object.h"
#include "ObjectArray.h"

class UClass : public UObject
{
	friend class FEngineLoop;

private:
	UClass* SuperClass;
	UObject* ClassDefaultObject;

public:
	wstring_view ClassName;
	const type_info& ClassTypeInfo;
	const size_t ClassSize;

	using ClassConstructorType = function<void(const FObjectInitializer&)>;
	ClassConstructorType ClassConstructor;

	using StaticClassFunctionType = function<UClass*(void)>;

	UClass() = delete;
	UClass(wstring_view InClassName, const type_info& InClassTypeInfo, const size_t InClassSize
		, ClassConstructorType InClassConstructor, StaticClassFunctionType InSuperClassFunction)
		: SuperClass(nullptr)
		, ClassDefaultObject(nullptr)
		, ClassName(InClassName)
		, ClassTypeInfo(InClassTypeInfo)
		, ClassSize(InClassSize)
		, ClassConstructor(InClassConstructor)
	{
		if (InSuperClassFunction)
		{
			SuperClass = InSuperClassFunction();
		}
	}

	virtual ~UClass() = default;

	UClass* GetSuperClass() const
	{
		return SuperClass;
	}

	template<class T>
	T* GetDefaultObject()
	{
		return (T*)GetDefaultObject();
	}

	UObject* GetDefaultObject(bool bNoCreate = true) const
	{
		if (ClassDefaultObject == nullptr && !bNoCreate)
		{
			InternalCreateDefaultObjectWrapper();
		}
		return ClassDefaultObject;
	}

protected:
	CORE_API void InternalCreateDefaultObjectWrapper() const;
	CORE_API virtual UObject* CreateDefaultObject();
};

CORE_API UClass* RegisterEngineClass (
	wstring_view InClassName,
	UClass::ClassConstructorType InClassConstructor,
	UClass::StaticClassFunctionType InSuperClassFunction,
	const type_info& InClassTypeInfo,
	const size_t InClassSize);

template<class T>
UClass* GetPrivateStaticClassBody (
	wstring_view InClassName,
	UClass::ClassConstructorType InClassConstructor,
	UClass::StaticClassFunctionType InSuperClassFunction
)
{
	PRINT_FUNCTION_NAME();
	const type_info& ClassTypeInfo = typeid( T );
	const size_t ClassSize = sizeof (T);
	UClass* NewClass = RegisterEngineClass (InClassName, InClassConstructor
		, InSuperClassFunction, ClassTypeInfo, ClassSize);
	return NewClass;
}

template<class T>
void InternalConstructor (const FObjectInitializer& X)
{

	PRINT_FUNCTION_NAME();
	FObjectInitializer* ObjectInitializer = const_cast<FObjectInitializer*>( &X );
	if (X.ObjectFlags & EObjectFlags::RF_ClassDefaultObject)
	{
		UObjectBase* ObjectBase = (UObjectBase*)GUObjectArray.Malloc (ObjectInitializer->Class->ClassTypeInfo);
		new( ObjectBase )UObjectBase (ObjectInitializer->Class, ObjectInitializer->ObjectFlags, ObjectInitializer->OuterPrivate);
		ObjectInitializer->Obj = static_cast<UObject*>( ObjectBase );
		T::__DefaultConstructor (X);
	}
	else
	{
		ObjectInitializer->ResultSharedPointer = Cast<T> (std::allocate_shared<T> (FAllocator<T> (*ObjectInitializer)));
	}
}

extern CORE_API map<wstring_view, UClass*> MapClass;