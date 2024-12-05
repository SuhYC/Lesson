# 람다식
익명 메소드를 만들기 위해 사용하는 식. <br/>
왜 람다냐면 당시 ```^```기호를 사용했는데 인쇄하기 어려운 문자라 비슷했던 소문자 람다를 사용했기 때문. <br/>
```매개변수목록=>식``` 과 같은 형태를 가진다. <br/>
```cs
delegate int Calculate(int a, int b);

Calculate calc = (int a, int b) => a + b; // 람다식을 delegate에 참조시킨다!
```

## 왜 delegate 익명 메소드와 동시에 제공되는가?
C# 3.0에 와서야 람다식이 도입되었는데 delegate문법은 C# 2.0에 이미 도입되었기 때문. <br/>
C# 2.0으로 많은 사람들이 익명 메소드를 사용했는데 람다식이 추가되어 기존 코드를 다 갈아엎기엔 그냥 동시 제공하는 기능으로 남기는게 낫다.

## 문 형식의 람다식
한줄로 함수가 구성되는 경우 식 하나로 해결이 되겠지만, <br/>
여러줄의 로직이 필요한 경우 중괄호를 이용해 코드 블록으로 하나의 식을 구성하면 된다. <br/>

```cs
delegate void DoSomething();

DoSomething DoIt = () => // 매개변수가 없는 경우 ()부분을 이렇게 비우면 된다.
    {
      Console.WriteLine("첫번째줄");
      Console.WriteLine("두번째줄");
      Console.WriteLine("세번째줄");
    };

DoIt();
```
