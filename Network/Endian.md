# 바이트 오더
어떤 데이터를 표기하기 위해 어떤 바이트에 먼저 기록할 지에 대한 기준. 

## 빅엔디안
상위 바이트가 앞에 오는 방식. <br/>
```0x12345678``` -> ```[12][34][56][78]``` <br/>
숫자를 왼쪽부터 읽는 직관성에 알맞은 방식이긴 하다. <br/>
IETF(인터넷 표준 기구)에서 네트워크 바이트오더를 빅엔디안으로 규정하면서 네트워크는 일반적으로 빅엔디안을 쓰기로 결정되었다.

## 리틀엔디안
하위 바이트가 앞에 오는 방식. <br/>
```0x12345678``` -> ```[78][56][34][12]``` <br/>
CPU연산에서 이점을 가져가는 경우가 많아서 정수연산, 포인터 오프셋 처리 등에서 유리하다. <br/>

### 하위 바이트부터 다루면 유리한 이유
정수형 데이터만 보더라도 1바이트, 2바이트, 4바이트, 8바이트로 여러 크기의 정수타입 데이터가 있다. <br/>
4바이트 정수타입에서 2바이트부분의 숫자만 사용하려고 한다면 하위 바이트 2개를 접근해야하는데, <br/>
이 경우 빅엔디안은 3번, 4번 바이트를 접근해야하지만, 리틀엔디안은 1번, 2번 바이트를 접근하면 된다. <br/>
이러한 이유로 CPU에서는 리틀엔디안이 유리한 점을 보이는데..

## 두 방식이 통일되지 않는 이유
네트워크는 이미 빅엔디안으로 오래 썼기에 많은 코드가 빅엔디안 기준으로 작성되었고, <br/>
CPU에서는 리틀엔디안이 유리하기 때문에, <br/>
기존 시스템을 전부 다 바꾸는 것은 사실상 불가능하며, 변환할 수 있는 프로그램은 두 방식을 변환해가며 사용하고, <br/>
일부 CPU에서는 둘 다 지원가능하도록 설계된다. <br/>
(ipv6로 전환하는게 더딘 이유랑도 어느정도 일맥상통한다.)
