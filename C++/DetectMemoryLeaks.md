# How To Detect Memory Leaks
## 메모리누수 탐지하기
서버는 일정기간동안 Run상태를 유지해야하기 때문에 메모리누수는 매우 치명적이다. <br/>
그렇기에 라이브서버를 구동하기 이전에 이미 누수는 없는지 탐지해야하는데, 이를 VS2022에서는 기능으로서 제공하고 있다.

### 준비사항

    #define _CRTDBG_MAP_ALLOC
    #include <cstdlib>
    #include <crtdbg.h>
    #ifdef _DEBUG
	    #ifndef DBG_NEW
		    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		    #define new DBG_NEW
	    #endif
     #endif // _DEBUG

먼저 위 코드를 포함하여야한다.<br/>
필요한 라이브러리를 포함하고, 자세한 설명을 표기할 옵션을 define한 뒤, new에 대한 새로운 정의를 적용한다. <br/>
단, 이 코드는 당연히 디버그를 위해 일정 오버헤드가 포함되기 때문에 릴리즈버전이 아닌 디버그모드에서 실행할 때 적용된다.

    #ifndef DBG_NEW

위 구문 안에 정의했기 때문.<br/>
다음으로는 애플리케이션의 종료부분마다

    _CrtDumpMemoryLeaks();

위 코드 삽입하기. 종료시점에 누수포인트를 찝어 출력부분에 표시해준다. <br/>
하지만 애플리케이션이 종료하는 시점이 여러개일 수도 있다. 그런 경우 일일히 모든 종료시점에 해당 코드를 적는것보다 편한 방법이 있다.

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

이 코드를 main()함수 첫문장으로 작성해주면 된다. 그러면 애플리케이션의 종료시점마다 자동으로 _CrtDumpMemoryLeaks()함수를 호출하게 된다.


    #define _CRTDBG_MAP_ALLOC
    #include <cstdlib>
    #include <crtdbg.h>
    
    #ifdef _DEBUG
      #ifndef DBG_NEW
        #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
        #define new DBG_NEW
      #endif
    #endif // _DEBUG

    #include <iostream>
    
    int main()
    {
      _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
      int* ptr = new int;
    
      return 0;
    }

위 코드를 실행하면

    Detected memory leaks!
    Dumping objects ->
    (실행한 소스의 주소)(19) : {154} normal block at 0x00000262C9709AB0, 4 bytes long.
     Data: <    > CD CD CD CD 
    Object dump complete.

이런 식으로 누수탐지 시 출력창에 결과가 표시된다.
