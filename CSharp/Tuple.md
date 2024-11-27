# 튜플
여러 필드를 담을 수 있는 구조체. <br/>
다만 구조체와 다른 점은 형식이름이 들어가지 않는다는 것. <br/>
System.ValueTuple구조체를 기반으로 만들어졌으며 컴파일러가 각 매개변수를 자동으로 Item1, Item2... 필드에 담는다. <br/>

```cs
var tuple = (123, 789);
```

## 명명된 튜플
필드의 이름을 지정할 수 있다. <br/>
```cs
var tuple = (Name: "John", Age: 30);
Console.WriteLine($"{tuple.Name}, {tuple.Age}");
```

명명했다고 Item1으로 접근할 수 없는건 아니다. <br/>
```cs
var tuple = (Name: "John", Age: 30);
Console.WriteLine($"{tuple.Item1}, {tuple.Item2}");
```

명명되지 않은 튜플과 명명된 튜플 사이에서도 필드의 수와 형식이 맞다면 할당이 가능하다. <br/>
```cs
var unnamed = ("Bob", 20); // string, int
var named = (Name: "John", Age: 30); // string, int

named = unnamed; // ("Bob", 20)
Console.WriteLine($"{named.Name}, {named.Age}");

named = ("Kate", 40);

unnamed = named; // ("Kate", 40)
Console.WriteLine($"{unnamed.Item1}, {unnamed.Item2}");
```

## 튜플 분해
튜플의 각 필드를 분해하여 다른 변수에 담을 수 있다. <br/>
각 원소가 필드의 순서대로 담기기 때문에 순서에 유의하여야한다. <br/>
```cs
var tuple = (Name: "John", Age: 30);
var (name, age) = tuple; // var name = "John"; var age = 30;
var (age2, name2) = tuple; // var age2 = "John; var name2 = 30; ?????
var (name3, _) = tuple; // var name3 = "John"; Age항목은 무시.
```

## 위치 패턴 매칭
튜플도 switch식에 사용할 수 있다. <br/>
```cs
var alice = (job: "학생", age: 17);

var discountRate = alice switch
{
    ("학생", int n) when n < 18 => 0.2,
    ("학생", _) => 0.1,
    (_, int n) when (n < 18) => 0.1,
    (_, _) => 0
};

Console.WriteLine(discountRate);
```
