# 트랜잭션 격리 수준
트랜잭션의 ACID원칙에 대해 엄밀하게 적용하는 것은 동시성의 하락으로 이어져 성능이 저하되며 [DeadLock](https://github.com/SuhYC/Lesson/blob/main/Operating_System/Deadlock.md)이 발생할 확률이 높아지게 된다. <br/>
이로 인해 트랜잭션의 격리 수준을 4단계로 구분하여 적용하게 된다.

## Read Uncommitted
해당 트랜잭션이 사용하는 데이터를 ```commit``` 또는 ```rollback```이전에 다른 트랜잭션이 읽는 것을 허용하는 격리수준이다. <br/>
이 경우 수정작업이 수행되는 도중에 다른 트랜잭션이 데이터를 읽을 수 있으므로 ```Dirty Read```가 발생한다. <br/>
이는 데이터의 정합성에 문제가 생기는 수준이기 때문에 데이터의 정합성이 중요하다면 사용하지 말아야한다.

## Read Committed
해당 트랜잭션이 사용하는 데이터를 다른 트랜잭션에서 접근할 경우 이전의 데이터로 읽는 것을 허용하는 격리수준이다. <br/>
이 경우 수정작업이 수행되었다고 가정하면 다른 트랜잭션에서 Non-Repeatable Read가 발생한다.
```commit```이전에 데이터에 접근하는 다른 트랜잭션에게 ```Undo```영역의 데이터를 제공한다.

#### Non-Repeatable Read
한 트랜잭션 내에서 같은 읽기 연산에 다른 결과를 발생시키는 현상. <br/>
트랜잭션 A와 B가 있다고 가정하자. <br/>
1. A : data C를 ```UPDATE```
2. B : data C를 ```SELECT``` // from Undo
3. A : ```COMMIT```
4. B : data C를 ```SELECT``` // 아까의 연산과 다른 값!

## Repeatable Read
트랜잭션이 수행되는 동안 같은 읽기연산에 대해 같은 결과를 보장하는 트랜잭션 격리 수준이다. <br/>
트랜잭션마다 트랜잭션 번호가 지정되며 자신보다 작은 번호의 트랜잭션이 변경한 사항에 대해서만 읽을 수 있다. <br/>
하지만 ```Phantom Read```현상이 발생할 수 있다.

#### Phantom Read
```Non-Repeatable Read```의 한 종류로, ```SELECT...WHERE```구문을 한 트랜잭션 내에서 같은 요청을 하더라도 다른 결과가 나타나는 현상이다. <br/>
이 경우는 새로운 행이 추가되고, 해당 행이 ```SELECT...WHERE```의 조건에 맞았을 경우 발생한다. <br/>
트랜잭션 A와 B가 있다고 가정하자. <br/>
1. B : ```SELECT...WHERE``` // 1|a, 2|b
2. A : ```INSERT INTO ... VALUES (3|c)
3. B : ```SELECT...WHERE``` // 1|a, 2|b, 3|c // 아까의 연산과 다른 값!

## Serializable
해당 트랜잭션이 사용하는 데이터를 다른 트랜잭션으로부터 완전 격리하는 격리수준이다. <br/>
다른 트랜잭션이 해당 행을 접근할 수 없으므로 동시성이 매우 떨어지며, <br/>
[DeadLock](https://github.com/SuhYC/Lesson/blob/main/Operating_System/Deadlock.md)의 문제도 발생할 수 있다.
