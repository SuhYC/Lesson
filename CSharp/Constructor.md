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

## 배열할당
어떤 객체의 배열을 할당한다고 가정하면, C++에서는 각각의 객체를 모두 생성자를 호출하여 초기화를 해준다. <br/>
하지만, C#에서는 배열을 할당할 때, 공간만 할당하고 각각의 데이터는 기본값으로 설정된다. <br/>

class의 객체 배열을 생성하면 참조타입이기 때문에 null로 초기화된 배열을 얻게 되고, <br/>
struct의 배열을 생성하면 값타입이기 때문에 기본값으로 초기화된 배열을 얻게 된다. <br/>

덕분에 실수를 하게 되는 경우가 있는데, <br/>
예를 들면 Color[] 배열을 생성하는 경우, <br/>
Color는 struct이며, 이 경우 r,g,b,a가 모두 0f로 초기화된다. <br/>
하지만 C#에 익숙하지 않고 C++만 익숙한 경우 당연히 r,g,b 값만 넣은 생성자가 a를 1f로 초기화 하기 때문에 a가 1f일 것이라고 생각할 수 있다. <br/>
앞서 설명한 것처럼 배열을 할당할 때에는 생성자를 호출하는 개념이 아니기 때문에 당연히 a는 0f로 초기화되어있다.
