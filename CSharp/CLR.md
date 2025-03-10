# Common Language Runtime
C# 프로그램은 운영체제나 하드웨어 바로 위에서 실행되는 것이 아닌 ```CLR```위에서 실행된다. <br/>
Java 프로그램이 ```JVM```을 통해 실행되는 것과 비슷하다.

## CLR을 통해 얻는 이점
1. 각각의 플랫폼에 최적화된 코드를 만들어 낼 수 있다.
CIL이라는 중간 언어로 작성된 실행 파일을 만들고, 이를 다시 하드웨어가 이해할 수 있는 네이티브 코드로 컴파일하여 실행한다. (Just In Time 컴파일)
2. 가비지컬렉션 기능을 제공한다.
자동으로 메모리를 관리하여 프로그래머가 할당, 해제할 필요가 없다.
3. 안정성
예외를 체계적으로 처리할 수 있는 메커니즘을 제공한다. 치명적 에러가 발생해도 프로그램 전체가 비정상종료되지 않도록 안전망을 제공한다.

## CLR의 단점
1. 컴파일 비용이 많이 든다.
CIL로 한번 실행파일을 만들고, 다시 네이티브코드로 컴파일하여 실행하니 컴파일비용이 많이 든다.
2. 메모리 사용량 증가
CLR자체도 메모리를 소모하며, 가비지컬렉션으로 인해 실행 중 갑자기 CPU사용량이 확 늘어난다거나 하는 일이 발생한다.
3. 로우레벨 작업 제약
C++처럼 직접 하드웨어를 제어하거나 최적화하는 것이 한계가 있다.
