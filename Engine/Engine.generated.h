#pragma warning(push)
#pragma warning(disable:4005)
#define GENERATED_BODY()\
public:\
DEFINE_DEFAULT_CONSTRUCTOR_CALL(UEngine)\
UEngine(const UEngine&) = delete;\
UEngine(const UEngine&&) = delete;\
UEngine& operator=(const UEngine&) = delete;\
UEngine& operator=(const UEngine&&) = delete;\
static UClass * StaticClass() { return UEngineRegisterEngineClass;}\
static inline UClass* UEngineRegisterEngineClass = \
	GetPrivateStaticClassBody<UEngine>(\
		TEXT("UEngine"),\
		(UClass::ClassConstructorType)InternalConstructor<UEngine>,\
		&UObject::StaticClass\
	);\
private:\
	using This = UEngine;\
	using Super = UObject;\

#pragma warning(pop)

