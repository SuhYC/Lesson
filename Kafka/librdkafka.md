# librdkafka
C++에서 kafka와 연동하기 위한 라이브러리. <br/>

## 기초 타입
```rd_kafka_t*``` : 클라이언트 인스턴스 핸들. producer 혹은 consumer 용도로 생성. 둘 다 각각 생성도 가능. <br/>
```rd_kafka_conf_t*``` : 설정 객체. producer를 만들 때마다 하나씩 생성하여 설정하여야하며, 해제의무는 producer객체가 갖는다. <br/>
```rd_kafka_topic_conf_t*``` : 토픽별 설정 객체.  <br/>
```rd_kafka_resp_err_t``` : 함수 오류 및 상태를 나타내는 enum.

## 인스턴스 생성 / 파괴
```rd_kafka_conf_new()``` : 새로운 설정 객체의 포인터를 반환. 실패하면 NULL. <br/>
```rd_kafka_conf_set(rd_kafka_conf_t *conf, const char *name, const char *value, char *errstr, size_t errstr_size)``` : conf 객체를 세팅. <br/>
#### 설정키(rd_kafka_conf_set의 파라미터 const char* name) <br/>
1. ```"bootstrap.servers"``` : 브로커 주소 (쉼표로 구분 가능)
2. ```"acks"``` : 프로듀서의 전송 확인 수준 (0, 1, all)
3. ```"retries"``` : 재시도 횟수
4. ```"linger.ms"``` : 배치 전송 지연(ms)
5. ```"batch.size"``` : 배치 최대 크기 (바이트 단위)
6. ```"enable.idempotence"``` : 중복 방지 모드 (true/false)
7. ```"security.protocol"``` : "SASL_SSL", "PLAINTEXT" 등 보안 프로토콜 지정
8. ```"group.id"``` : 컨슈머 그룹 ID
9. ```"auto.offset.reset"``` : "earliest" / "latest"
10. ```"enable.auto.commit"``` : 오프셋 자동 커밋 여부 (true/false)

```rd_kafka_new(rd_kafka_type_t type, rd_kafka_conf_t *conf, char *errstr, size_t errstr_size)``` : kafka 클라이언트 핸들 반환. 실패시 NULL. <br/>
type : ```RD_KAFKA_PRODUCER``` 또는 ```RD_KAFKA_CONSUMER``` <br/>

```rd_kafka_flush(rd_kafka_t *rk, int timeout_ms)``` : producer에 한해 남아있는 모든 전송 요청이 완료될 때까지 최대 timeout_ms만큼 블록. <br/>
```rd_kafka_consumer_close(rd_kafka_t *rk)``` : consumer에 한해 Kafka 클러스터와의 세션 정리, 리밸런스 처리, 오프셋 커밋, 그룹 탈퇴 등 정리 절차. <br/>

```rd_kafka_destroy(rd_kafka_t *rk) / rd_kafka_destroy_flags(rd_kafka_t *rk, int flags)``` : kafka핸들(rd_kafka_t*)을 해제. <br/>
```rd_kafka_flush``` 또는 ```rd_kafka_consumer_close```의 함수를 핸들타입에 맞게 호출한 후에 해제하여야한다. <br/>
flags 버전에서는 flush나 close를 기다리지 않고 종료하는 비정상종료가 가능한데, 데이터의 정합성을 보장하지 않기 때문에 테스트환경 등에서만 사용할 것을 권장. <br/>

## Producer 관련
```rd_kafka_topic_new(rd_kafka_t *rk, const char *topic, rd_kafka_topic_conf_t *topic_conf)``` : 토픽 핸들 생성. 실패시 NULL. <br/>
발급한 토픽 핸들은 사용이 끝나면 ```rd_kafka_topic_destroy(rd_kafka_topic_t* rkt)```로 해제. <br/>

```rd_kafka_produce(rd_kafka_topic_t *rkt, int32_t partition, int msgflags, void *payload, size_t len, const void *key, size_t keylen, void *msg_opaque)``` : 신규메시지 생성. <br/>
비동기로 메시지를 내부 큐에 넣고 백그라운드로 카프카에 전송. <br/>

```rd_kafka_poll(rd_kafka_t *rk, int timeout_ms)``` : 내부 이벤트 콜백 호출. <br/>
```rd_kafka_flush(rd_kafka_t *rk, int timeout_ms)``` : 남아있는 모든 전송 요청이 완료될 때까지 최대 timeout_ms만큼 블록. <Br/>

## Consumer 관련
```rd_kafka_subscribe(rd_kafka_t *rk, rd_kafka_topic_partition_list_t *topics)``` : 컨슈머 그룹 방식으로 토픽 리스트 구독. <br/>
리밸런스 콜백(rebalance_cb)을 conf로 등록해 offset commit/partition assign 등을 처리. <br/>

```rd_kafka_consumer_close(rd_kafka_t *rk)``` : 그룹에서 나가며 리소스 정리. <br/>

```rd_kafka_poll(rd_kafka_t *rk, int timeout_ms)``` : 이벤트, 메시지 처리. callback함수 실행. <br/>
```rd_kafka_consume(rd_kafka_topic_t *rkt, int32_t partition, int timeout_ms)``` : 해당 파티션의 하나의 메시지 또는 에러를 기다림. <br/>
실패시 NULL. 반환된 메시지는 소비 후에 ```rd_kafka_message_destroy(rd_kafka_message_t* rkm)```. <br/>

```rd_kafka_consumer_poll(rd_kafka_t *rk, int timeout_ms)``` : 이벤트, 메시지 처리 및 반환.(내부적으로 ```rd_kafka_poll``` 사용 후 fetch queue에서 반환)<br/>
```rd_kafka_poll``` + ```rd_kafka_consume```의 과정을 래퍼해놓은 high-level API라고 생각하면 됨. <br/>
마찬가지로 반환된 메시지는 소비 후 ```rd_kafka_message_destroy(rd_kafka_message_t* rkm)```. <br/>

```rd_kafka_consume_batch(rd_kafka_topic_t *rkt, int32_t partition, int timeout_ms, rd_kafka_message_t **rkmessages, size_t rkmessages_size)``` : 한번의 N개까지 배치로 가져옴. <br/>
```rd_kafka_consume_callback(rd_kafka_topic_t *rkt, int32_t partition, int timeout_ms, void (*consume_cb)(rd_kafka_message_t *rkmessage, void *opaque), void *opaque)``` : 콜백기반으로 배치 처리. 타임아웃 인자 포함.<br/>

```rd_kafka_commit(rd_kafka_t *rk, const rd_kafka_topic_partition_list_t *offsets, int async)``` : 동기 오프셋 커밋. <br/>
```rd_kafka_commit_message(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, int async)``` : 비동기 오프셋 커밋. <br/>
오프셋 커밋 함수 2개는 ```rd_kafka_poll()```, ```rd_kafka_consume```, ```rd_kafka_consume_batch``` 사용 시 명시적으로 오프셋을 변경시켜줘야하는데, 이 때 사용함. <br/>

```rd_kafka_seek(rd_kafka_topic_partition_t *rktpar, int64_t offset, int timeout_ms)``` : 특정 오프셋으로 이동(파티션별). <br/>
```rd_kafka_position(rd_kafka_t *rk, rd_kafka_topic_partition_list_t *partitions)``` : 현재 consumer가 읽을 오프셋 위치 쿼리. <br/>

## 기타 유틸리티
```rd_kafka_outq_len(rd_kafka_t *rk)``` : 아직 전송되지 않은(out-queue) 메시지 수. <br/>
```rd_kafka_name(const rd_kafka_t *rk)``` : 클라이언트 이름 조회.
