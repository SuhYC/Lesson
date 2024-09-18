# DB Normalization
관계형 데이터베이스의 데이터를 정리하여 중복을 제거하고 무결성을 유지하는 방법.

## 제1정규형 (1NF)
```필드의 값은 원자적이어야한다.```<br/>
예를 들어,<br/>
```
    Name   |  Item  
    Alice  |  Coin, Card
    Tom    |  Sword
```
와 같이 구성되어 있다면, Alice의 Item항목은 현재 2개의 데이터를 표시하고 있다.<br/>
이를 다음과 같이 변경하는 것이 ```제1정규형```이다.<br/>
```
    Name   |  Item
    Alice  |  Coin
    Alice  |  Card
    Tom    |  Sword
```

## 제2정규형 (2NF)
```제1정규형을 만족하는 테이블에 대해 완전함수종속을 만족해야한다.```<br/>
다르게 말하자면, ```기본키의 부분집합에 의존하는 속성이 없어야 된다.```<br/>
예를 들어,<br/>
```
    Name    |  Item   |  Cost  |  ExpirationDate
    Alice   |  Coin   |  50    |  2024/09/19
    Alice   |  Card   |  100   |  2025/04/29
    Tom     |  Sword  |  1500  |  Null
    Tom     |  Card   |  100   |  2024/12/25
```
와 같이 테이블이 구성되어있다고 가정하자.<br/>
Name과 Item가 복합키로, 해당 키를 이용해 ExpirationDate를 조회할 수 있다. <br/>
하지만 Cost는 Item에 의존하고 있다. (Item의 종류만 알면 상점판매가는 동일하다.)<br/>
그러면 ```제2정규화```를 통해 다음과 같이 테이블을 변경할 수 있다.
```
    Name    |  Item  |  ExpirationDate
    Alice   |  Coin  |  2024/09/19
    Alice   |  Card  |  2025/04/29
    Tom     |  Sword |  Null
    Tom     |  Card  |  2024/12/25
--------테이블 분리!------
    Item   |  Cost
    Coin   |  50
    Card   |  100
    Sword  |  1500
```

## 제3정규형 (3NF)
```제2정규형을 만족하는 테이블에 대해 이행적 종속이 없어야한다.```<br/>
다르게 말하자면, ```A->B, B->C일때, A->C의 관계가 한 테이블에 존재하면 안된다.```<br/>

예를 들어, <br/>
```
    CharacterName  |  GuildName  |  GuildMaster
    JohnNarSen     |  Heart      |  Zizon
    KingWangZzang  |  Lion       |  Warrior
    NewBie         |  Happy      |  Nyehuing
```
와 같이 테이블이 구성되어 있다고 가정하자.<br/>
CharacterName에 대해 가입한 길드정보 GuildName은 ```A->B```관계이다.<br/>
GuildName에 대해 해당 길드의 길드마스터 GuildMaster는 ```B->C```관계이다.<br/>
한 테이블 내에 ```A->B->C```의 관계가 모두 드러나 있으며, 이를 이행적 종속이라고 한다.<br/>
(이 테이블은 제2정규형을 만족한다. 해당 릴레이션은 기본키 CharacterName만 존재하기 때문.)<br/>
그러면 ```제3정규화```를 통해 다음과 같이 테이블을 변경할 수 있다.
```
    CharacterName  |  GuildName
    JohnNarSen     |  Heart
    KingWangZzang  |  Lion
    NewBie         |  Happy
---------테이블 분리!------
    GuildName  |  GuildMaster
    Heart      |  Zizon
    Lion       |  Warrior
    Happy      |  Nyehuing
```

## 보이스코드정규형 (BCNF)
추후 작성.
