# 생성자
객체를 생성할 때 호출되는 함수. <br/>
클래스와 이름이 같으며 반환형식이 없다. <br/>
오버로딩이 가능하며 명시적으로 생성자를 구현하지 않으면 컴파일러에서 기본생성자를 만든다. <br/>

## this() 생성자
자기자신의 생성자를 지목한다. <br/>
생성자 내에서만 호출할 수 있으며, 인수정보를 포함하여 어떤 생성자를 먼저 실행할 지 결정한다. <br/>
```cs
class MyClass
{
    public MyClass()
    {
        Console.WriteLine("this()");
    }

    public MyClass(int a) : this()
    {
        Console.WriteLine("this(a)");
    }

    public MyClass(int a, int b) : this(a)
    {
        Console.WriteLine("this(a,b)");
    }
}

static void Main()
{
    MyClass myClass = new MyClass(1,2);

}
```

결과 :
```
this()
this(a)
this(a,b)
```
