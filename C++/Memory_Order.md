# Memory Order
## 메모리 접근 순서

코드의 명령어 순서는 실제 실행의 순서와 다를 수 있다.

### 컴파일러의 입장
먼저 컴파일러는 해당 코드를 어셈블리 코드로 변환하는 과정에서 최대한 효율적인 실행을 위해 어셈블리 코드의 순서가 바뀌는 일이 있을 수 있다. <br/>
예시 코드는 다음과 같다.

    a = 0;
    b = 0;
 
    a = b + 1;
    b = 1;

위 코드의 하위 2줄을 컴파일하였을 때, 어셈블리 코드가 다음과 같이 나타날 수 있다.

    mov eax, DWORD PTR b[rip]   // reg = b
    mov DWORD PTR b[rip], 1     // b = 1
    add eax, 1                  // reg++ 
    mov DWORD PTR a[rip], eax   // a = reg

b = 1에 해당하는 연산이 a = b + 1에 해당하는 연산 사이에 수행되고 있다. <br/>
물론 결과는 우리가 생각하는 결과와 같다. a, b에 모두 1이 들어가게 된다. <br/>
컴파일러는 결과가 바뀌지 않는 선에서 [CPU Pipelining](https://github.com/SuhYC/Lesson/blob/main/Computer_Structure/CPU_Cycle.md)을 고려해 더 나은 순서로 실행할 수 있도록 어셈블리화한다.

이러한 과정은 멀티스레드환경 + Cache환경에서 예상되지 않은 결과를 낳을 수 있는데 이를 해결해주는 것이 Memory_Order이다.

### Memory_Order
atomic<T> 함수에 사용할 수 있는 인자이다.

    atomic<T>::store(T desired_, std::memory_order order_);
    atomic<T>::load(std::memory_order order_);

#### std::memory_order_relaxed
가장 느슨한 조건으로 주위의 다른 메모리 접근과 순서가 바뀌어도 무방함을 의미한다. <br/>
메모리연산 순서에 관련해 최대한의 자유를 부여하기 때문에 CPU에서 매우 빠른 속도로 실행된다. <br/>
하지만 앞서 설명한 예상되지 않은 결과가 나타날 수 있으니 제약조건이 필요한 상황이 있을 수 있다.

#### std::memory_order_acquire
해당 명령 뒤에 오는 모든 메모리 명령들이 해당 명령 위로 재배치되는 것을 금지한다. <br/>
특정 변수가 확인되고 이후 연산을 수행해야될 경우에 사용한다.

#### std::memory_order_release
해당 명령 앞에 있는 모든 메모리 명령들이 해당 명령을 넘어가서 재배치되는 것을 금지한다. <br/>
앞선 명령들이 모두 수행되는 것을 확정짓고 다음 명령을 수행해야할 때 사용한다.

두 스레드 간에 한 스레드가 모두 일을 마친 후에 다른 스레드가 이어서 작업해야하는 경우
선행스레드가

    is_ready.store(true, std::memory_order_release);
    
로 작업을 마치고
후행스레드가

    while (!is_ready.load(std::memory_order_acquire)) {}
    
로 동기화하여 이어 작업할 수 있다.
