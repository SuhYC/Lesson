# switch

## 패턴 매칭
switch문의 일반적인 사용은 C++과 동일하나, C#은 object의 타입(형식)에 따라 분기할 수 있다. <br/>
ex.
```CSharp
object obj = 4;

switch(obj)
{
  case int: // 여기로 분기된다!
    ...
    break;
  case float:
    ...
    break;
  default:
    ...
    break;
}

```

## 케이스가드
또한 케이스가드와 같은 기능도 C#에선 제공한다.

ex.
```CSharp
switch(obj)
{
    case int:
      ...
      break;
    case float f when f >= 0: // 추가 조건을 걸어 true일때 진행한다.
      ...
      break;
    case float:
      ...
      break;
    default:
      ...
      break;
}
```

## switch 식
간단한 코드로 switch문을 대체할 수 있다. <br/>
ex.
```CSharp
string grade = score switch // score값에 따라 grade에 다음 식을 대입한다.
{
  90 => "A", // 90 이상이라면 "A"를
  80 => "B",
  70 => "C",
  60 => "D",
  _ => "F" // default:
};
```
또한 switch식에서도 케이스가드를 사용할 수 있다.
