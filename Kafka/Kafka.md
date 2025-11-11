# Kafka
분산형 이벤트 스트리밍 플랫폼. <br/>

# 특징
1. 높은 처리량: 초당 수백만 건의 메시지 처리 가능
2. 확장성: Broker를 추가하면 쉽게 확장
3. 내결함성: 데이터를 여러 파티션에 복제 가능
4. 실시간 스트리밍: Producer가 보내는 데이터를 거의 실시간으로 Consumer가 읽을 수 있음

# 사용목적
서버 아키텍쳐 내 안전한 메시지 전달. <br/>
각각의 컨슈머그룹이 어디까지 데이터를 처리했는지 관리하기 때문에 1:N의 복잡한 메시지 관리도 수월하게 진행 가능 <br/>

# 메시지 전송 보장 (Delivery Semantics)
Kafka에서는 Producer -> Broker -> Consumer 과정에서 메시지의 전달을 보장하는 방식을 선택할 수 있다. <br/>

## At most once
최대 한 번 전달, 메시지 손실 허용, 중복 없음. <br/>
메시지를 한 번 보내고 확인 없이 버림. <br/>
장점 : 중복 걱정 없음. <br/>
단점 : 메시지가 손실될 수 있음. <br/>

## At least once
최소 한 번 전달, 메시지 손실 없음, 중복 가능 <br/>
Producer는 Broker가 메시지를 받았는지 확인하고, 실패하면 재전송. <br/>
Consumer는 같은 메시지를 중복해서 읽을 수 있음. <br/>
장점 : 메시지 손실 없음 -> 중요한 정보를 안전하게 처리할 수 있음 <br/>
단점 : 중복 처리 로직 필요 (Consumer 쪽에서 deduplication 필요.)

## Exactly once
정확히 한 번 전달, 메시지 손실 없음, 중복 없음 <br/>
Producer -> Broker, Broker -> Consumer의 과정에서 모두 ACK를 확인하여 중복 제거. <br/>
장점 : 안전하고 중복 걱정 없음 <br/>
단점 : 두 과정에서 모두 로직이 추가되므로 오버헤드로 성능이 떨어질 수 있음. <br/>

### 손실??? TCP를 사용하는게 아닌가요?
TCP를 사용함. TCP상에서가 아닌, 중간 처리 과정에서 실패가 발생하는 경우가 손실이 발생할 수 있음. <br/>
일반적인 TCP서버에서도, L7버퍼문제나, 연결 끊김 등의 문제로 송신에 대한 모든 응답이 보장되지 않는 경우가 있음. <br/>
Kafka 또한 브로커가 다운된 상태였다던지 하는 경우에 메시지가 손실될 수 있으나, 이를 Delivery Semantics 설정을 통해 방지할 수 있음. <br/>

# 용어
## Producer
데이터를 만들어서 Kafka로 보내는 주체. <br/>
예: 게임에서 유저 행동 로그 생성, 센서 데이터 전송

## Topic
데이터가 쌓이는 "카테고리"나 "채널" <br/>
예: user-login, game-event, trade-log

## Partition
Topic은 여러 파티션으로 나뉘어 저장. 각 파티션은 순서가 유지되는 로그 구조를 가짐. <br/>
데이터 병렬 처리와 확장성을 위해 사용

## Consumer
Topic에서 데이터를 읽는 주체 <br/>
여러 Consumer가 하나의 Topic을 나눠 읽을 수도 있고(Consumer Group), 각자 다 읽을 수도 있음

## Consumer Group
여러 Consumer가 하나의 그룹으로 묶여서 데이터를 나눠 처리함 <br/>
하나의 메시지는 한 Consumer Group 안에서는 한 번만 처리됨

## Broker
Kafka 서버 자체. 여러 대의 서버가 클러스터를 이루어 데이터를 저장하고 복제
