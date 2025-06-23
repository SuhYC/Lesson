# 소켓 통신 기술 및 API

## BSD 소켓 (POSIX Sockets)
리눅스 및 유닉스 계열에서 사용할 수 있는 가장 기본적인 소켓API. <br/>
Windows의 winsock과 유사하다. <br/>
동기식 소켓 기반.
#### 주요함수
```socket()```, ```bind()```, ```listen()```, ```accept()```, ```connect()```, ```send()```, ```recv()```, ```close()```

## Winsock (Windows Socket API)
Windows에서 BSD 소켓 스타일의 통신을 지원하기 위한 API. <br/>
Windows 전용 확장 함수를 지원한다. <br/>
여러가지 I/O 모델 제공 (select, WSAEventSelect, overlapped I/O, IOCP ...)

#### 주요함수
```WSAStartup()```, ```WSARecv()```, ```WSASend()```

## select / poll
여러 소켓을 감시하여 데이터 수신 여부를 확인하는 다중 I/O 처리 기법. <br/>
다양한 운영체제에서 지원된다. <br/>
싱글스레드에서 다중 소켓 처리를 지원하기 위해 사용. <br/>
많은 동접이 필요하지 않는 상태에서 사용하기 좋다. <br/>
입출력 가능 여부만 알려주기 때문에 I/O처리는 별도로 해줘야함. <br/>
송신처리 시 blocking이 걸릴 수 있다. <br/>
소켓 입출력 상태 알림도 동기, I/O 처리도 동기. <br/>

폴링 방식으로 이벤트가 발생한 소켓을 찾는다. <br/>
리눅스 환경에서는 poll을 사용하고, windows 환경에서는 select를 사용한다.

## WSAEventSelect
소켓 I/O 입출력 가능 여부를 Event 객체를 통해 비동기로 알려줌. (I/O처리는 동기) <br/>
Select 모델처럼 매번 소켓을 운영체제에 전달하지 않아도 됨. <br/>
관찰대상의 소켓을 운영체제로 한번만 전달해 사용할 수 있음. <br/>
해당 소켓의 입출력 가능 여부 이벤트가 발생되면 이벤트 객체를 통해 시그널 상태가 됨. <br/>
```WSAWaitForMultipleEvents()```함수를 통해 여러개의 소켓의 입출력 가능 여부를 알 수 있음. <br/>

이벤트 통지 방식이라는 점에서 IOCP와 비슷하지만, 하나의 스레드당 최대 64개의 이벤트 감시가 가능하다는 차이가 있다. <br/>
64개 소켓을 초과한 연결을 감시하려면 스레드를 더 할당하여 64 * N개의 감시가 가능하다. <br/>
그리고 I/O 통지 또한 WSAEventSelect는 준비완료, IOCP는 작업완료 라는 차이가 있다.

## epoll / kqueue
리눅스 환경에서 사용되는 이벤트 기반 비동기 I/O 모델.

## overlapped I/O
IOCP의 기반이 되는 비동기 I/O 방식. <br/>
송수신 함수 호출 시 작업이 즉시 반환되고 실제 작업완료는 나중에 알림을 통해 통지. <br/>
(I/O 요청 시 지연 없이 리턴, 실제 I/O작업은 비동기로 진행) <br/>
```WSASocket()```에서 ```WSA_FLAG_OVERLAPPED```플래그로 소켓을 생성할 수 있다. <br/>
```WSASend()```, ```WSARecv()```를 통해 비동기 I/O요청을 할 수 있다. <br/>
결과 통지는 다음 중 하나로 알림이 도착한다. <br/>
1. 이벤트 객체 (Manual Event)
2. Completion Routine (콜백)
3. IOCP 큐

## IOCP
Windows 환경에서 쓸 수 있는 가장 강력한 비동기 멀티스레드 I/O 모델. <br/>
Overlapped I/O 방식을 사용하여 송수신 동작 까지도 비동기로 수행할 수 있는 완전 비동기 모델이다. <br/>
소수의 스레드가 다수의 연결을 처리할 수 있는 M:N 모델. <br/>
워커스레드가 IOCP 큐로부터 완료된 I/O동작에 대한 결과를 받아 후처리를 진행한 후 다시 GQCS함수를 통해 스레드풀에서 다른 결과처리를 기다린다. <br/>
```WSAEventSelect```방식에 비해 스레드가 특정 연결에 묶여있지 않은 구조이며, 하나의 스레드가 맡을 수 있는 연결의 제한도 없어 대규모 유저를 처리할 수 있다.

## Windows 환경에서의 소켓서버 방식
1. 1:1의 스레드-소켓 연결방식 (Blocking 소켓 기반)<br/>
2. 1:N의 스레드-소켓 연결 및 폴링 방식 (select)<br/>
3. 1:N의 스레드-소켓 연결 및 이벤트 통지 방식 (non-blocking I/O + WSAEventSelect) <br/>
4. M:N의 비동기I/O 및 이벤트 통지 방식 (완전 비동기 I/O 기반 모델, Overlapped I/O + IOCP) <br/>
