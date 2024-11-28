# 배열
같은 형식의 데이터를 연속적인 주소에 담는 자료구조. <br/>
```cs
int[] arr = new int [5];
arr[0] = 1;
```

## System.Index
C# 8.0부터 도입된 기능. ```^```연산자도 사용할 수 있다. <br/>
```^n```은 인덱스로서```arr.Length-n```과 같다. <br/>
```cs
System.Index last = ^1;
scores[last] = 34; // scores[scores.Length - 1] = 34;

scores[^1] = 34; // scores[scores.Length - 1] = 34;
```

## Collection Initializer (컬렉션 초기자)
다음과 같이 중괄호로 배열을 초기화할 수 있다. <br/>
```cs
string[] array1 = new string[3] {"안녕", "Hello", "Hi"};
string[] array2 = new string[] {"안녕", "Hello", "Hi"}; // 배열의 크기를 생략해도 초기자의 원소에 맞게 크기를 할당한다.
string[] array3 = {"안녕", "Hello", "Hi"}; // new와 형식을 생략해도 초기자의 원소에 맞게 할당한다.
```
위 세가지 초기화 방법 중 협업에 도움되는 방식을 선택하면 된다.

## System.Array
C# .NET의 Common Type System에서 배열은 System.Array 클래스에 대응된다. <br/>
다음과 같은 메소드를 사용할 수 있다. <br/>

- 정적 메소드
1. Sort() : 정렬.
2. BinarySearch<T>() : 이진탐색.
3. IndexOf() : 찾고자 하는 특정 데이터의 인덱스를 반환.
4. TrueForAll<T>() : 모든 요소가 해당 조건에 부합하는지 여부를 반환.
5. FindIndex<T>() : 지정한 조건에 부합하는 첫번째 요소의 인덱스를 반환.
6. Resize<T>() : 배열의 크기를 재조정
7. Clear() : 배열의 모든 요소를 초기화.
8. ForEach<T>() : 배열의 모든 요소에 대해 동일한 작업을 수행
9. Copy<T>() : 배열의 일부를 다른 배열에 복사

- 인스턴스 메소드
1. GetLength() : 배열에서 지정한 차원의 길이를 반환.
- 프로퍼티
1. Length() : 배열의 길이를 반환
2. Rank() : 배열의 차원을 반환

## System.Range
C# 8.0에서 도입된 기능. 시작 인덱스와 마지막 인덱스를 이용해 범위를 나타낸다. <br/>
```cs
System.Range r1 = 0..3;
int[] sliced = scores[r1]; // scores배열의 0~2인덱스에 대응하는 부분 (마지막 인덱스는 제외된다.)

int[] sliced = scores[0..3]; // scores[r1]과 동일.
```
시작인덱스를 생략하면 배열의 첫번째 요소를 시작인덱스로 간주하며 마지막 인덱스를 생략하면 마지막 요소 다음 위치를 마지막 인덱스로 간주한다. <br/>
```cs
int[] whole = scores[..]; // 모든 요소를 가져온다.
```
System.Index 객체를 이용할 수도 있다.
```cs
int[] sliced = scores[..^1]; // 마지막 요소를 마지막 인덱스로 간주하며, 이는 마지막 원소를 제외하고 가져오는 것과 같다.
```

## 다차원 배열
C++과 다른 점은 대괄호를 1번만 쓰고 콤마로 구분한다는 점. <br/>
```cs
int[,] array = new int[2,3];
array[0,1] = 2;

int[,] array2 = new int[2,3] {{1,2,3},{4,5,6}}; // 형식과 길이 명시
int[,] array3 = new int[,] {{1,2,3},{4,5,6}}; // 배열 길이 생략
int[,] array4 = {{1,2,3},{4,5,6}}; // 형식과 길이 생략
```
마찬가지로 협업에 도움되는 방식을 선택하면 된다. <br/>
단, 3차원 배열 이상을 자주 사용하는 것은 가독성을 떨어뜨린다.

## 가변 배열
대괄호 여러개를 사용하여 길이를 조절할 수 있는 배열을 선언할 수 있다. <br/>
```cs
int[][] jagged = new int[3][];
jagged[0] = new int[5]{1,2,3,4,5};
jagged[1] = new int[] {10, 11, 12};
jagged[2] = new int[] {100, 101}; // 아쉽게도 이때는 형식을 초기화하지 못한다!
```
