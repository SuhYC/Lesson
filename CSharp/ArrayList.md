# ArrayList
동적배열을 이용한 자료구조. <br/>
Array와 비슷하게 작동하지만, 몇가지 차이점이 있다. <br/>

1. 동적 크기를 갖는다.
ArrayList는 요소가 가득찬 상태에서 새로운 원소를 추가하면 그 크기를 2배로 늘린 새로운 공간을 할당하고, 데이터를 옮긴 후 새로운 원소를 추가한다. <br/>
다음과 같은 코드는 새로운 크기의 배열을 할당하지만, 데이터를 옮겨주지 않기 때문에 기존 데이터가 사라진다. <br/>
```cs
int[] arr = { 1, 2, 3 };
arr = new int[5];
Console.WriteLine(arr[0]); // 0이 출력!
```

2. 타입안정성이 고려되지 않는다.
ArrayList는 타입을 지정하여 저장하지 않는다. <br/>
```cs
ArrayList ar = new ArrayList();
ar.Add("1"); // int형 데이터를 받으려고 했다면 잘못된 동작을 유도할 수도 있다!
Console.WriteLine(ar[0]);

List<int> list = new List<int>();
list.Add("1"); // 에러!!
```

다음과 같은 메소드를 사용할 수 있다.
1. Add() : 마지막 요소 뒤에 새로운 요소 추가
2. RemoveAt() : 특정 인덱스에 있는 요소 제거
3. Insert() : 원하는 위치에 새 요소 삽입

일반적으로는 List를 사용하는 것이 권장된다.

## 배열을 이용한 컬렉션 초기화
배열을 사용해서 컬렉션을 초기화할 수 있다. <br/>
```cs
int[] arr = {123, 456, 789};
ArrayList list = new ArrayList(arr); // list: [123][456][789]
ArrayList list2 = new ArrayList(){123, 456, 789}; // list2: [123][456][789]
```
마지막 방식은 ```IEnumerable```인터페이스와 ```Add()```메소드를 구현한 컬렉션만 지원한다. <br/>
그러므로 ```Queue```와 ```Stack```은 컬렉션초기자가 아닌 배열을 직접 넘기는 방식으로 초기화해야한다.
