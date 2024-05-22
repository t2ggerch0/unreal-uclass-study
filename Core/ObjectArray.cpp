#include "ObjectArray.h"

CORE_API FUObjectArray GUObjectArray;

void FMemoryPool::Create(const string_view InName, const size_t InSizePerOne)
{
    if (Pool)
    {
        return;
    }

    Name = InName;
    Pool = new boost::pool<>(InSizePerOne);
    SizePerOne = InSizePerOne;
}

void* FMemoryPool::Malloc()
{
    void* Address = Pool->malloc();
    return Address;
}

void FMemoryPool::Free(void* InAddress)
{
    Pool->free(InAddress);
}

void FMemoryPool::Destroy()
{
    if (Pool)
    {
        delete Pool;
        Pool = nullptr;
    }
}

void FUObjectArray::Create(const type_info& InType, const size_t InSizePerOne)
{
    MapMemoryPool[InType.hash_code()].Create(InType.name(), InSizePerOne);
}

void* FUObjectArray::Malloc(const type_info& InType)
{
    return MapMemoryPool[InType.hash_code()].Malloc();
}

void FUObjectArray::Free(const type_info& InType, void* InAddress)
{
    MapMemoryPool[InType.hash_code()].Free(InAddress);
}

void FUObjectArray::Destroy()
{
    for (auto& It : MapMemoryPool)
    {
        It.second.Destroy();
    }
    MapMemoryPool.clear();
}
