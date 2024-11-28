# 스택
LIFO의 형태로 동작하는 자료구조 <br/>
새로운 데이터는 맨 위에 삽입되며, 처리할 데이터는 맨 위부터 처리된다.

## 함수
1. Push() : 새로운 데이터를 맨 위에 쌓는다.
2. Pop() : 쌓여있는 데이터 중 가장 위 데이터를 가져온다.
- 요소가 없는데 요청하면 System.InvalidOperationException를 발생시킨다.

## 예제
```cs
Stack st = new Stack(); // 제네릭 없이 써도 되긴 한다! 이 경우 object타입으로 매개변수를 인식한다.
st.Push(1); // st: [1]
st.Push(2); // st: [2][1]

int a = (int)st.Pop(); // int a = 2;, st: [1]
```

## 배열을 이용한 초기화
배열로 초기화할 수 있다. <br/>
```cs
int[] arr = {123, 456, 789};
Stack st = new Stack(arr); // st: [789][456][123]
```
다만 컬렉션초기자를 직접 사용하여 초기화하는 것은 불가능하다. <br/>
컬렉션초기자는 ```IEnumerable```인터페이스와 ```Add()```메소드를 구현하는 컬렉션만 지원한다. <br/>
Stack은 ```IEnumerable```인터페이스는 상속하지만 ```Add()```메소드는 구현하지 않는다.
```cs
Stack st = new Stack(){123, 456, 789}; // 에러!
```
