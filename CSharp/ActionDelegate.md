# Action 대리자
반환형식이 없는 메소드를 참조하기 위한 대리자. <br/>
입력매개변수가 0개인 것부터 16개인 것까지 17가지의 ```Action 대리자```가 존재한다. <br/>

```cs
Action act1 = () => Console.WriteLine("Action()"); // 입력매개변수가 없는 Action 대리자.
int result = 0;
Action<int> act2 = (x) => result = x * x; // 람다식 밖에서 선언한 result에 x*x를 저장.
```
