# Context Switching

## 문맥교환

현재 진행중인 실행흐름을 중단하고 저장한 후, 다음 실행흐름을 불러와 실행하는 과정이다. <br/>
이 경우 멀티프로세싱과 멀티스레딩을 고려할 수 있는데,

### 멀티프로세싱
멀티프로세싱이란 다수의 프로세스를 사용하여 진행하는 것을 의미한다.<br/>
프로세스는 각각 고유한 코드, 데이터, 스택, 힙 영역을 가지고 있다.<br/>
그러므로 프로세스를 문맥교환할 때에는 위 4개 영역과 PC register를 모두 저장하고 불러와야한다.

### 멀티스레딩
멀티스레딩이란 다수의 스레드를 사용하여 진행하는 것을 의미한다.<br/>
스레드는 하나의 프로세스 내에 여러개 존재할 수 있으며 프로세스가 가지고 있던 코드, 데이터, 힙 영역을 공유받아 접근할 수 있다.<br/>
그러므로 스레드를 문맥교환할 때에는 스택과 PC register만 저장하고 불러오면 된다.

## 그러면 어느 것이 좋을까?
문맥교환의 오버헤드는 멀티프로세싱 쪽이 크다. <br/>
그러면 멀티스레딩을 권장하는가? 꼭 그런건 아니다.

### 멀티프로세싱의 장단점
#### 장)프로그램 안정성 : 각 프로세스 중 일부가 에러로 인해 진행할 수 없는 경우라고 하더라도 나머지 프로세스는 진행가능하다.
#### 장)시스템 확장성 : 동일한 프로세스를 여러개 만들어 시스템의 규모를 쉽게 확장할 수 있다. (서버 클러스터)
#### 단)문맥교환 비용 : 멀티스레딩에 비해 문맥교환 시 수행해야 하는 동작이 많아 오버헤드가 크다.
#### 단)자원교환 비효율 : 멀티프로세싱은 각각의 프로세스가 다른 메모리 영역을 갖는다. 다른 프로세스와 통신하여 데이터를 넘겨줄 수 있지만, 비효율적이다.

### 멀티스레딩의 장단점
#### 장)문맥교환 비용 : 멀티프로세싱에 비해 문맥교환 시 수행해야 하는 동작이 적어 오버헤드가 작다.
#### 장)자원의 효율성 : 스레드 간에는 코드, 데이터, 힙 영역을 공유하여 시스템 자원 소모가 줄어든다.
#### 장)가벼운 용량 : 공유하는 메모리 영역에 대한 추가적인 할당이 필요하지 않으므로 용량을 적게 차지한다.
#### 단)프로그램 안정성 : 스레드 중 하나라도 문제가 발생하여 중단되면, 해당 프로세스의 모든 스레드가 진행할 수 없게될 수 있다.
#### 단)동기화 비용 : 스레드가 동시에 같은 자원에 접근하면 엉뚱한 값을 읽어오거나 저장할 수 있다. 이를 막기 위해 동기화가 필요하며 일부 성능 저하가 발생한다.