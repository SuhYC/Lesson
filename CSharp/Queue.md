# 큐
FIFO의 형태로 동작하는 자료구조. <br/>
새로운 데이터는 뒤로 추가되며 처리할 데이터는 앞부터 처리된다. <br/>

## 함수
1. Enqueue() : 새로운 데이터를 가장 뒤에 추가한다.
2. Dequeue() : 큐에 있는 요소 중 가장 앞에 있는 요소를 Pop하여 반환한다.

## 예제
```cs
Queue que = new Queue(); // 제네릭 없이 써도 되긴 한다! 이 경우 object타입으로 매개변수를 인식한다.
que.Enqueue(1); // que: [1]
que.Enqueue(2); // que: [1][2]
int a = que.Dequeue(); // int a = 1;, que: [2]
```

## 배열을 이용한 초기화
배열로 초기화할 수 있다. <br/>
```cs
int[] arr = {123, 456, 789};
Queue que = new Queue(arr); // que: [123][456][789]
```
다만 컬렉션초기자를 직접 사용하여 초기화하는 것은 불가능하다. <br/>
컬렉션초기자는 ```IEnumerable```인터페이스와 ```Add()```메소드를 구현하는 컬렉션만 지원한다. <br/>
```Queue```는 ```IEnumerable```인터페이스는 상속하지만 ```Add()```메소드는 구현하지 않는다. <br/>
```cs
Queue que2 = new Queue(){123, 456, 789}; // 에러!
```
