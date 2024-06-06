# Single Instruction Single Data
한 번에 한 개씩의 명령어와 데이터를 순서대로 처리하는 단일 프로세서 시스템
파이프라이닝, 슈퍼스칼라
### 파이프라이닝
흔히 멀티스레딩. [시간적 병렬성](https://github.com/SuhYC/Lesson/blob/main/Computer_Structure/CPU_Cycle.md)(temporal parallelism)을 이용한 중첩계산(overlapped computation)을 수행.   
### 슈퍼스칼라
파이프라인을 처리할 수 있는 코어를 여러 개 구성하여 복수의 명령어가 동시에 실행되도록 하는 방식.   
파이프라이닝과 비슷하지만 각 단계에서 동시에 실행되는 명령어가 2개.   
오늘날의 CPU는 대부분 슈퍼스칼라를 사용.

# Single Instruction Multiple Data
배열프로세서 (Array Processor).   
하나의 명령어를 다수의 데이터들에 대하여 동시 실행.   
-> 다수의 데이터에 대하여 동일한 연산 실행   
공간적 병렬성(spatial parallelism)을 실현하기 위해 여러 개의 동기화된 ALU들로 구성되는 시스템.

# Multiple Instruction Single Data
각 프로세서들은 서로 다른 명령어들을 실행하지만 처리하는 데이터들은 하나의 스트림.   
자주 쓰이지 않음.

# Multiple Instruction Multiple Data
대부분의 병렬 컴퓨터들이 해당.   
밀결합 시스템 (tightly-coupled system)
 - 프로세서들이 공유 기억장치(shared memory)를 이용하여 데이터 교환.
소결합 시스템 (loosely-coupled system)
 - 프로세서들이 메시지 전송(message passing)을 이용하여 데이터 교환.
시스템 자원(기억장치, 입출력장치)들을 공유하는 여러 개의 프로세서들을 이용해 비동기적 병렬성(asynchronous parallelism)을 실현하는 시스템.

## 배열프로세서 vs 다중프로세서
SI vs MI.   
동일한 프로그램을 수행하느냐, 별도의 프로그램을 비동기적(독립적)으로 수행하느냐.
