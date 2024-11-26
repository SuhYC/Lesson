# 메소드 숨기기
CLR에게 기반클래스버전의 메소드를 감추고 파생클래스에서 구현된 버전만 보여주는 기능. <br/>
파생클래스 버전의 메소드를 new한정자로 수식하여 해당 기능을 사용할 수 있다. <br/>
기반클래스의 메소드를 숨긴다는 점에서 오버라이딩과 헷갈릴 수 있으나, <br/>
부모클래스 타입에 객체를 집어넣고 실행할 때의 동작이 다르다. <br/>

오버라이딩 :
```cs
class Base
{
    public virtual void Do()
    {
        Console.WriteLine("Base.Do()");
    }
}

class Derived : Base
{
    public override void Do()
    {
        Console.WriteLine("Derived.Do()");
    }
}


static void Main()
{
    Base b = new Derived();
    b.Do(); // "Derived.Do()"
}
```
메소드 숨기기 :
```cs
class Base
{
    public void Do()
    {
        Console.WriteLine("Base.Do()");
    }
}

class Derived : Base
{
    public new void Do()
    {
        Console.WriteLine("Derived.Do()");
    }
}


static void Main()
{
    Base b = new Derived();
    b.Do(); // "Base.Do()"
}
```
