## Getting started
+ binaries/Start.exe 실행 시 아래의 과정을 통해 Engine Tick이 수행됩니다
+ Engine.generated.h의 GENERATED_BODY 매크로를 통해 UClass 객체를 생성합니다
+ Start 프로젝트의 main 함수에서 Launch 모듈의 GuardedMain을 호출하여 EngineLoop에 진입합니다
+ Engine 모듈의 PreInit에서 CDO를 생성합니다
+ Engine 모듈의 Init에서 NewObject를 통해 GEngine 객체를 생성합니다
+ GEngine에서 Tick이 수행되고 esc키가 입력되면 Exit가 호출됩니다