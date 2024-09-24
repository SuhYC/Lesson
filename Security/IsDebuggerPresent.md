# IsDebuggerPresent()
## 디버거 감지 함수
### Windows API

```cpp
#include <iostream>
#include <Windows.h>

int main()
{
  if(IsDebuggerPresent() != 0)
  {
    std::cout << "Detected!";
  }

  return 0;
}
```
위 코드를 디버깅 시작하면 if문 내로 진입하여 문자열이 출력된다. <br/>
하지만 디버깅하지 않고 시작하면 아무 일 없이 종료된다. <br/>

```IsDebuggerPresent(void)```함수는 Windows API 중 하나로, 현재 프로세스에 연결된 디버거가 있는지 확인하는 함수이다. <br/>
만약 디버거가 연결되어있다면 ```0이외의 값```이, 연결되어 있지 않다면 ```0```이 리턴된다. <br/>

```CheckRemoteDebuggerPresent()```와 ```NtQueryInfomationProcess()```를 통해서도 디버거 유무를 조사할 수 있다.<br/>
(위 두 함수 내용은 추후 추가.) <br/>

이러한 함수를 통해서 애플리케이션에 접근하여 역공학을 시도하는 경우를 어느정도 방어할 수 있으나,<br/>
```Hooking``` 등의 방법으로 우회가 가능하다...

## C#
```C#```에서는 ```System.Diagnostics.Debugger```클래스를 이용할 수 있다. <br/>
```Debugger.IsAttacked```를 호출하여 bool값을 리턴받을 수 있다.
