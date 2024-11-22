# 예외처리를 통한 결과 통지 vs Enum값을 이용한 결과 통지

이례적으로 폴더로 구성해 README와 코드를 첨부함 <br/>
이왕 코드도 만들어서 테스트해본 겸 업로드.

## 결과통지는 어떤게 빠를까?
모종의 이유로 함수 내부에서 해당 동작이 실패했음을 판단하고 결과를 통지할 때, <br/>
```throw Exception("msg");```를 하는게 좋을까?<br/>
아니면 ```return RETCODE::REASON;```을 하는게 좋을까? (물론 RETCODE버전은 이유마다 Enum값을 만들어주어야한다.) <br/>

예외처리를 통한 통지의 경우는 실패한 이유를 그대로 msg로 적어 보내면 그만이고, <br/>
Enum 리턴값을 통한 통지의 경우는 상황에 맞는 Enum값을 만들고,<br/>
해당 Enum값에 대해 클라이언트에 결과 전달이 필요한 경우 문자열을 작성해 전송해주어야한다. <br/>

예외처리가 편한 부분이 많을 것이다.<br/>
어차피 문자열로 구성해 클라이언트에게 전달이 필요한 부분이면 e.what()을 통해 응답메시지를 바로 만들 수 있으니. <br/>
하지만 속도면에서는 Enum통지를 따라오지 못할 것 같다. <br/>

당연히 enum class를 사용하면 일반 정수형을 사용하는 것과 동일한 속도를 가져올 수 있다. <br/>
하지만 예외처리를 사용하면
1. 예외객체 자체의 생성자와 소멸자 처리
2. 스택 언와인드에 따른 다른 객체의 소멸자 처리
3. 예외처리기 검색

이 세가지의 오버헤드가 발생하게 되는데, <br/>
물론 2번은 함수 내부에서 실패가 확정되고 결과를 통지하며 리턴할 것이기 때문에 상관이 없다.<br/>
Enum을 써도 동일한 오버헤드가 발생할 것이다. <br/>

3번의 경우는 적절한 catch문을 찾기 위한 시간으로,<br/>
하나의 사용자정의예외만을 생성하고 에러메시지만 커스텀하는 방식으로 어느정도 처리는 가능할 것이다. <br/>

1번에서 차이가 발생하는 것으로 보인다. <br/>
상기한 내용처럼, enum은 타입안전을 고려한 정수형변수나 다름 없기 때문에 굉장히 빠르게 선언하고 복사하며 처리할 수 있다. <br/>
하지만 예외처리의 경우는 예외객체를 생성해야하며, 다양한 예외를 하나의 예외클래스로 대체하려면, 에러메시지를 보관할 공간이 필요하다. <br/>
또한 ```std::exception```을 상속하기 때문에 ```(내 작업환경 기준)``` 최소 24바이트의 공간을 차지한다.

## 테스트
총 세가지로 나누어 테스트한다.
1. 예외를 발생시키는 함수를 만들고 try-catch를 통해 메시지를 출력한다.
2. RETCODE를 리턴하는 함수를 만들고 unordered_map을 통해 함수포인터를 저장하고 해당 함수를 호출한다.
3. RETCODE를 리턴하는 함수를 만들고 switch문을 통해 순회하여 해당 함수를 호출한다.

세가지 모두 출력은 동일하게 ```std::cout << "Fail" << "\n";```. <br/>
기본적으로 해야하는 조건확인은 수행한다. (```itr = map.find(); if(itr != map.end()){...}```)<br/>
5회 정도 실행하고 걸린 시간을 측정한다.
```
1번 : 2659, 2417, 2712, 2463, 2494
2번 : 598, 645, 581, 576, 631
3번 : 553, 584, 612, 632, 540

평균 : 2549, 606.2, 584.2
```

## 결과 분석
1번 케이스가 예상한 대로 가장 오래걸린다. <br/>
2번 케이스와 3번 케이스는 결과에 따른 처리함수 호출에 있어 발생한 차이인데, <br/>
```unordered_map```은 ```hashmap```이다. ```hash```함수를 수행하고 해당 버킷의 데이터를 가져오는 방식. <br/>
hash함수가 입력데이터의 길이와 관계없이 ```O(1)```을 보장한다 해도, ```n```이 충분히 작을 때 ```O(n)```에 밀릴 여지가 있다. <br/>
선형탐색을 한다고 해도 코드의 구성에는 2가지케이스 밖에 없기 때문에 3번 케이스가 유리하게 나왔을 것이다.

### 그럼 Enum통지와 int리턴통지는 비교 안해도 되나?
int값을 리턴하는 건 코드 가독성이 너무 떨어진다. <br/>
그나마가 ```const int RETCODE_SOMECASE = 0;``` 이런 방식인데 이건 굳이 Enum으로 할 수 있는데 그럴 이유가 없다.

### vector에 함수포인터를 저장해서 호출하면 ```hash```함수를 수행할 필요 없이 O(1)으로 검색가능하지 않을까?
추후 Enum이 수정되거나 하는 경우에 일일히 코드에 반영해주어야한다. <br/>
Enum에 맞는 인덱스에 적절한 함수가 매핑되어야하는데 유지보수할 때 헷갈린다. <br/>
3번케이스가 굉장히 작은 n으로 수행되었기 때문에 기대효과는 미미해보인다.