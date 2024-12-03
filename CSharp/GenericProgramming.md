# 일반화 프로그래밍
데이터 형식을 일반화하여 타입 안전성을 유지하면서도 코드 재사용성과 유연성을 높이는 프로그래밍 기법. <br/>

## 일반화 메소드
메소드의 매개변수나 반환값의 타입을 형식 매개변수(이후 코드에서 <T>)를 통해 일반화할 수 있다. <br/>
```cs
void CopyArray<T>(T[] source, ref T[] target)
{
  if (target.Length < source.Length)
  {
    Array.Resize(ref target, source.Length);
  }

  for (int i = 0; i < source.Length; i++)
  {
    target[i] = source[i];
  }
}
```

## 일반화 클래스
클래스의 멤버의 형식을 일반화한 클래스. <br/>
```cs
class Array_Generic<T>
{
  private T[] array;
  // ...
  public T GetElement(int index) { return array[index]; }
}
```
```cs
Array_Generic<int> intArr = new Array_Generic<int>();
```

## 형식 매개변수 제약시키기
특정한 조건을 갖춘 형식에만 대응하는 형식 매개변수가 필요한 경우 사용. <br/>
```cs
class MyList<T> where T : MyClass
{
 //...
}

void CopyArray<T>(T[] source, T[] target) where T : struct
{
  if (target.Length < source.Length)
  {
    Array.Resize(ref target, source.Length);
  }

  for (int i = 0; i < source.Length; i++)
  {
    target[i] = source[i];
  }
}
```
1. ```where T : struct``` : T는 값 형식이어야 한다.
2. ```where T : class``` : T는 참조 형식이어야 한다.
3. ```where T : new()``` : T는 반드시 매개변수가 없는 생성자가 있어야 한다.
4. ```where T : MyClass``` : T는 명시한 기반클래스(MyClass부분)의 파생클래스여야 한다.
5. ```where T : IEnumerable``` : T는 명시한 인터페이스(IEnumerable부분)를 반드시 구현해야한다.
6. ```where T : U``` T는 또 다른 형식 매개변수 U로부터 상속받은 클래스여야 한다.

## 일반화 컬렉션
컬렉션을 특정 타입에 대해 타입안정성을 갖는 형태로 선언할 수 있다. <br/>
1. ```ArrayList``` -> ```List<T>```
2. ```Queue``` -> ```Queue<T>```
3. ```Stack``` -> ```Stack<T>```
4. ```Hashtable``` -> ```Dictionary<Tkey, Tvalue>```
