#pragma once

enum EInternal { EC_InternalUseOnlyConstructor };

#define DEFINE_DEFAULT_CONSTRUCTOR_CALL(TClass) \
static void __DefaultConstructor(const FObjectInitializer& X) { new((EInternal*)X.GetObj())TClass; } \
virtual void __DefaultDestructor() override {this->~TClass();}
#define DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(TClass) \
static void __DefaultConstructor(const FObjectInitializer& X) { new((EInternal*)X.GetObj())TClass(X); } \
virtual void __DefaultDestructor() override {this->~TClass();}

#define GENERATED_BODY()
#define UCLASS(...)
#define UPROPERTY()

enum EObjectFlags
{
	RF_NoFlags = 0x00000000,
	RF_ClassDefaultObject = 0x00000010
};

