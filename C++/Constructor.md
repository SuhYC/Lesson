# 생성자
객체가 생성될 때 호출되는 함수. <br/>
리턴값은 없다. 가상함수로 선언될 수 없다. <br/>
private으로 선언될 수는 있다 (싱글톤 패턴이라던가.. 다른 곳에서 생성자 호출못하게.)

## 기본 생성자
매개변수가 하나도 없는 생성자. <br/>
클래스의 생성자를 하나도 구현하지 않으면 기본 생성자를 컴파일러가 제공한다. <br/>
이 말은 역으로 매개변수가 있는 생성자가 하나라도 구현되어 있다면, 명시적으로 기본 생성자를 구현하지 않으면 기본 생성자가 제공되지 않는다는 이야기다.

## 명시적으로 삭제된 생성자
static 함수만 구현된 클래스는 생성자가 필요없다. <br/>
기본 생성자도 필요 없으니 명시적으로 생성자를 삭제할 수 있다.
```cpp
class MyClass
{
public:
  MyClass() = delete;
};
```

## 복사 생성자
다른 객체와 똑같은 객체를 생성하는 특수 생성자이다. <br/>
반드시 원본 객체에 대한 const 레퍼런스를 매개변수로 받는다. <br/>
대부분의 컴파일러는 복사 생성자를 명시적으로 구현하지 않으면 복사 생성자를 만들어준다.

객체가 값으로 반환될 때, 값으로 인자로 넘겨질 때, 다른 원본 객체로 초기화될 때, 임시 객체를 만들 때 호출된다.

### 대입 연산자와 복사 생성자의 차이
대입 연산자는 이미 생성된 객체에 원본 객체를 대입하는 연산자이다. const 멤버에 유의할 것.

## 이동 생성자
우측값 레퍼런스로 원본 객체를 매개변수로 받는 특수 생성자이다.

### 이동 대입 연산자에서 주의할 점
자기 자신이 매개변수로 오지는 않았는지 확인해야한다.

## 매개변수가 하나인 생성자
매개변수가 하나인 생성자가 있는 경우 해당 생성자는 ```Conversion Constructor```가 되어 해당 타입의 매개변수가 대입되는 경우에 호출된다.
```cpp
class A
{
public:
  A(int i) { std::cout << "Constructor Called!\n";}
};

int main()
{
  A a(10); // Constructor Called!
  a = 10; // Constructor Called!

  return 0;
}
```

## 생성자와 예외
생성자에서 예외를 던질 수는 있다.<br/>
단, 생성자 내에서 동적할당을 직접 한 경우는 예외를 던지기 전, 반드시 해당 메모리를 해제하고 예외를 던져야한다.<br/>

```cpp
class A
{
public:
	A(int i) { std::cout << "Constructor Called!\n"; }
	~A() { std::cout << "Destructor Called!\n"; }
};

class B
{
public:
	B() : a(new A(1))
	{
		throw std::bad_alloc();
	}

	~B()
	{
		std::cout << "B Cleans a!\n";
		if (a != nullptr)
		{
			delete a;
		}
	}

private:
	A* a;
};

int main()
{
	try
	{
		B b;
	}
	catch (std::bad_alloc&)
	{

	}

	return 0;
}
```
결과:```Constructor Called!```

위 예제에서 B객체를 생성하며 A객체를 동적할당하여 멤버변수를 초기화하고, 예외를 던진다. <br/>
그러면 B의 소멸자에서 delete를 호출하며 a를 해제할 것 같지만, B의 소멸자는 호출되지도 않는다. <br/>
생각해보면 B의 생성에 실패했으니 소멸자를 호출할 일도 없는 것이다. <br/>
그러니 반드시 B객체의 생성자에서 예외를 던지기 전 이미 a를 해제하는 동작이 들어갔어야한다.


## 멤버 이니셜라이저
C++의 생성자에서는 멤버를 초기화하는 멤버이니셜라이저를 사용할 수 있는데, <br/>
자원을 소유한 객체일 수록 멤버이니셜라이저를 사용할 것을 권장한다. <br/>
그 이유는 다음 코드를 보면 알 수 있는데, <br/>

```cpp
class ResourceObject
{
public:
    ResourceObject()
    {
        std::cout << "Constructor.\n";
    }
    ResourceObject(const ResourceObject& other_) noexcept
    {
        std::cout << "Copy Constructor.\n";
    }

    ResourceObject& operator=(ResourceObject&& rhs_) noexcept
    {
        std::cout << "operator= R-v.\n";

        return *this;
    }
    ResourceObject& operator=(const ResourceObject& other_) noexcept
    {
        std::cout << "operator= L-v.\n";

        return *this;
    }
};

class A
{
public:
    A(ResourceObject& obj) : data(obj)
    {

    }

private:
    ResourceObject data;
};

class B
{
public:
    B(ResourceObject& obj)
    {
        data = obj;
    }
private:
    ResourceObject data;
};

int main() {
    ResourceObject obj;

    std::cout << "A Test Start.\n";

    A a(obj); // 멤버 이니셜라이저로 초기화!

    std::cout << "B Test Start.\n";

    B b(obj); // 본문 내 초기화

    return 0;
}
```
위 코드를 실행하면, <Br/>
멤버 이니셜라이저로 초기화한 쪽은 바로 복사생성자가 호출되며 1번의 함수 호출로 완료된다. <br/>
하지만 본문 내 초기화는 기본생성자가 호출되고, 대입연산자가 호출되며 2번의 함수 호출로 완료된다. <br/>

C++의 객체 내 멤버 중 class타입 멤버는 멤버이니셜라이저가 명시되어 있지 않다면 기본생성자가 호출된다. <br/>
할당과 동시에 초기화가 진행되고, 이후에 생성자가 호출되어 본문 초기화를 하기 때문에, <br/>
자원을 관리하는 객체 멤버를 본문 내 초기화하게 되면, 기본생성자와 대입연산자가 호출되므로 비효율적이다. <br/>
자원을 관리하는 객체 멤버는 되도록 멤버 이니셜라이저를 사용해 복사생성자만 호출하도록하여 오버헤드를 줄이자.
