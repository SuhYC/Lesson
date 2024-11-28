# 프로퍼티
Java에는 없는 개념이다. <br/>
Java에서는 Getter메소드, Setter메소드를 사용하여 필드에 접근한다. <br/>
C#에서는 Getter메소드, Setter메소드를 쓸수도 있지만, 프로퍼티 기능을 제공하여 좀 더 편리하게 사용할 수 있도록 한다. <br/>

## 구현
프로퍼티를 선언하고 싶은 필드에 대해 다음과 같이 구현한다. <br/>
```cs
class MyClass
{
  private int myField;
  public int MyField
  {
    get
    {
      return myField;
    }
    set
    {
      myField = value;
    }
  }
}
```

## 사용
설정한 프로퍼티를 사용하여 데이터를 저장하거나 데이터를 읽어올 수 있다. <br/>
```cs
MyClass obj = new MyClass();
obj.MyField = 3; // set
Console.WriteLine(obj.MyField); // get
```

## 읽기 전용 프로퍼티
```set```부분을 구현하지 않으면 읽기 전용이 된다.
```cs
class MyClass
{
  private int myField;
  public int MyField
  {
    get
    {
      return myField;
    }
  }
}
```

## 쓰기 전용 프로퍼티
```get```부분을 구현하지 않으면 쓰기 전용이 된다...만 그 용도와 동작 결과를 확인할 수 있는 방법을 알릴 수 있어야한다. <br/>
쓰기를 사용한 결과를 알기 어려운 코드는 유지보수를 어렵게 한다.

## 자동 구현 프로퍼티
C# 3.0부터 도입된 기능. <br/>
```cs
class MyClass
{
  public int MyField
  {
    get; set;
  }
}
```
더 나아가 C# 7.0부터는 자동구현프로퍼티에 초기화를 수행할 수 있다. <br/>
```cs
class MyClass
{
  public int MyField{get; set;} = 3;
}
```

## 프로퍼티와 생성자
생성자를 호출할 때, 프로퍼티를 이용한 초기화를 할 수 있다. <br/>
```cs
BirthdayInfo birth = new BirthdayInfo()
  {
    name = "서현",
    Birthday = new DataTime(1991, 6, 28)
  };
```

## 초기화 전용 자동 구현 프로퍼티
C# 9.0에 도입된 기능. init 접근자를 사용할 수 있다. <br/>
```set```이 선언되지 않았기 때문에 수정은 불가능하지만 초기화는 가능하다. <br/>
```cs
public class Transaction
{
  public string From {get; init;}
  public string To {get; init;}
  public int Amount {get; init;}
}
```

## required
수식하는 프로퍼티를 객체를 초기화할 때 반드시 초기화하도록 컴파일 수준에서 강제한다. <br/>
```cs
class MyClass
{
  public required int MyField {get; init;}
}
```

## record
C# 9.0부터 사용 가능 <br/>
값형식처럼 다룰 수 있는 불변 참조형식이다. <br/>
record 키워드와 초기화 전용 자동 구현 프로퍼티를 사용해 선언한다. <br/>
쓰기 가능한 프로퍼티와 필드도 사용할 수 있다.

```cs
record RTransaction
{
  public string From {get; init;}
  public string To {get; init;}
  public int Amount {get; init;}
}
```

## with를 통한 record 복사
C# 컴파일러는 레코드 형식을 위한 복사생성자를 자동으로 작성한다. <br/>
단, 이 복사생성자는 ```protected```로 선언되기 때문에 명시적으로 호출할 수 없고, with 식을 이용한다. <br/>
```cs
RTransaction tr1 = new RTransaction{From = "Alice", To = "Bob", Amount = 100};
RTransaction tr2 = tr1 with {To = "Charlie"};
```
만약 다음과 같이 사용한다면 해당 레코드참조 자체를 복사한 것이고 새로운 객체를 만든 것이 아니다. <br/>
```cs
RTransaction tr1 = new RTransaction{From = "Alice", To = "Bob", Amount = 100};
RTransaction tr2 = tr1;
```
그리고 다음과 같이 사용한다면 새로운 객체를 만들어 기존 레코드 내용을 복사한 것이다. <br/>
```cs
RTransaction tr1 = new RTransaction{From = "Alice", To = "Bob", Amount = 100};
RTransaction tr2 = tr1 with {};
```

## 무명 형식
두 개 이상의 같은 형식의 인스턴스를 사용하지 않을 것이라면 무명 형식을 통해 간단히 인스턴스를 만들 수 있다. <br/>
무명 형식으로 만든 인스턴스에 할당된 값은 변경불가능하다.
```cs
var myInstance = new {Name = "psyc", Age = 123);
```
