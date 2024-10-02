# Memory Pool
메모리를 사용 시마다 할당/해제하는 것이 아니라 <br/>
미사용 노드를 자료구조로 모아두고 사용할 때 가져다 쓰고 다 쓴 후 다시 자료구조에 반납하는 방식으로 메모리를 사용하는 것.

## 장점
```new``` 와 ```delete```는 생각보다 오버헤드가 크다. <br/>
그런 의미에서 메모리를 재할당하지 않고 재사용하여 해당 비용을 줄일 수 있다.

## 단점
그때 그때마다 사용할 메모리보다 여유있는 메모리를 미리 할당해두어야 하기 때문에 비교적 많은 메모리를 쓰게 된다.

## 주의사항
멀티스레드 환경에서 사용할 때 주의하여야한다. <br/>
먼저, 락을 걸고 메모리풀에서 데이터를 가져오는건 그다지 비용적 이득이 없다. <br/>
그러므로 원자적연산을 시도하여야하는데, 이 경우 [ABA Problem](https://github.com/SuhYC/Lesson/blob/main/Operating_System/ABA_problem.md)이 발생할 수 있다. <br/>
ABA Problem을 해결할 수 있는 방법을 도입한 이후 사용하여야한다.


### 예시
[LockFreeStack](https://github.com/SuhYC/DIY/blob/main/LockFreeStack/FileName.cpp)
