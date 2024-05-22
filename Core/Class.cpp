#include "Class.h"
#include "ObjectMacros.h"
#include "ObjectArray.h"
#include "ObjectGlobals.h"

CORE_API map<wstring_view, UClass*> MapClass;

CORE_API void UClass::InternalCreateDefaultObjectWrapper() const
{
    const_cast<UClass*>(this)->CreateDefaultObject();
}

CORE_API UObject* UClass::CreateDefaultObject()
{
    PRINT_FUNCTION_NAME();
    _ASSERT (!ClassDefaultObject);
    const size_t SharedPtrSize = sizeof(_Ref_count_obj_alloc3<UObject, FAllocator<UObject>>) - sizeof (UObject);
    GUObjectArray.Create(ClassTypeInfo, ClassSize + SharedPtrSize);

    FStaticConstructObjectParameters StaticConstructObjectParameters(this);
    StaticConstructObjectParameters.SetFlags = EObjectFlags::RF_ClassDefaultObject;

    FObjectInitializer ObjectInitializer{StaticConstructObjectParameters};
    ClassConstructor(ObjectInitializer);
    ClassDefaultObject = ObjectInitializer.GetObj();

    return ClassDefaultObject;
}

CORE_API UClass* RegisterEngineClass (wstring_view InClassName
    , UClass::ClassConstructorType InClassConstructor,
    UClass::StaticClassFunctionType InSuperClassFunction
    , const type_info& InClassTypeInfo, const size_t InClassSize)
{
    PRINT_FUNCTION_NAME();
    GUObjectArray.Create(typeid(UClass), sizeof(UClass));
    UObjectBase* ObjectBase = (UObjectBase*)GUObjectArray.Malloc(typeid(UClass));

    FObjectInitializer ObjectInitializer{EObjectFlags::RF_ClassDefaultObject};
    new(ObjectBase)UObjectBase(ObjectInitializer.Class, ObjectInitializer.ObjectFlags
        , ObjectInitializer.OuterPrivate);

    UClass* NewClass = new(ObjectBase)UClass(InClassName, InClassTypeInfo
        , InClassSize, InClassConstructor, InSuperClassFunction);
    MapClass.insert(make_pair(InClassName, NewClass));

    return NewClass;
}
