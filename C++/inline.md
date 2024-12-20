# 인라인
함수 선언에 사용하여 ```인라인 함수```로 만들도록 요청할 수 있다. <br/>
```인라인 함수```는 매크로만큼 오버헤드 걱정을 줄여주고, 매크로보다 안전하다. <br/>
요즘은 컴파일러가 자동으로 적절한 함수를 인라인화 해주기도 한다.

## 매크로와 비교
```매크로```는 ```#define```을 통해 사용할 수 있으며, 해당 텍스트를 치환하여 코드전처리를 진행한다. <br/>
```inline```은 컴파일러가 해당 함수를 인라인화할 것인지 판단한다. <br/>

```매크로```와 동일하게 함수 호출문을 본문으로 바꿔치기하여 목적코드의 크기를 증가시킨다. <br/>

```매크로```는 텍스트 치환만 수행하므로 의도하지 않은 결과가 발생할 수 있다. <br/>
```cpp
#include <iostream>
#define SQUARE(x) (x * x)

int main()
{
  std::cout << SQUARE(1+2+3); // (1+2+3 * 1+2+3) -> 11?
  return 0;
}
```

```매크로```는 디폴트인자를 사용할 수 없지만, ```인라인 함수```는 가능하다. <br/>
```cpp
inline int plus(int a, int b = 5)
{
  return a + b;
}
```

## 주의사항
1. 생성자와 소멸자는 인라인으로 만들지 않는다.
2. 재귀함수로 만들지 않는다.
3. 함수포인터로 인라인함수를 호출하는 경우 인라인되지 않는다.
4. 조건문과 반복문이 포함된 긴 코드는 인라인화하지 않는다.