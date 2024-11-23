# 소멸자
객체가 소멸할 때 호출되는 함수. <br/>
```~<ClassName>()```와 같이 작성되며 매개변수 없이 작성되며 리턴타입은 없다. <br/>
스택에 생성된 객체가 해당 스코프가 끝날 때 자동으로 호출되고, 힙에 생성된 객체는 delete를 통해 명시적으로 소멸할 때 호출된다. <br/>
소멸자의 수는 1개를 초과할 수 없다.

## private 소멸자
싱글톤 패턴 등으로 객체의 생성 및 소멸과 같은 과정을 통제하기 위해 사용한다. <br/>
static 메소드 내에 static 객체를 리턴하는 형식으로 구현하여 싱글톤 패턴으로 쓸 수도 있고, <br/>
프렌드 함수로 객체를 소멸시킬 수도 있으며, <br/>
특정 멤버함수 내에서 객체를 정리할 수 있도록 할 수도 있다.

```cpp
class A
{
public:
	A(int i) { std::cout << "Constructor Called!\n"; }

	void End()
	{
		delete this; // 멤버함수에서 호출하는건 가능!
	}

private:
	~A() { std::cout << "Destructor Called!\n"; } // private!
};

int main()
{
	A* pA = new A(1);

	//delete pA;
	pA->End();

	return 0;
}
```

## 소멸자와 예외
소멸자는 외부로 예외를 발생시킬 수 없다. 소멸자 내에서 발생한 예외는 반드시 소멸자 안에서 처리해야한다. <br/>
소멸자는 명시적으로 ```noexcept(false)```를 지정하지 않거나 클래스에 ```noexcept(false)```소멸자가 있는 하위 객체가 없다면 noexcept로 선언된 것으로 취급한다. <br/>
noexcept 소멸자에서 익셉션을 던지면 C++런타임은 std::terminate()를 호출해 프로그램을 종료한다. <br/>

## 함수 내의 스택에서 선언된 객체는 소멸자가 언제 호출될까?
함수의 리턴값이 결정되고, 이후에 소멸자가 호출된다.
```cpp

int i;

class A
{
public:
	A() { i = 3; }
	~A() { i = 5; }
};

int func()
{
	A a;
	return i;
}

int main()
{
	std::cout << func() << '\n'; // 3
	std::cout << i;              // 5
	return 0;
}
```
위 코드의 리턴값이 3으로 결정된 뒤, A의 소멸자가 호출되어 i가 5로 바뀐다.

## 배열로 선언된 객체는 어느 순서대로 생성자와 소멸자가 호출될까?
```[0][1][2]```처럼 3칸 배열로 객체를 생성하면, 0, 1, 2 순으로 생성자가 호출되며 2, 1, 0 순으로 소멸자가 호출된다.

## virtual 소멸자
소멸자를 virtual로 선언하면 어떻게 될까? <br/>
객체의 생성시에는 반드시 객체의 타입을 명시하게 되어있는 반면에, 객체의 소멸시에는 변수명을 사용하게 된다. <br/>
따라서 상속관계에 있는 클래스의 경우는, 부모 객체의 포인터에 자식 객체의 인스턴스가 있는 경우가 있는데, <br/>
이 경우 부모 객체로 판단하고 부모객체의 소멸자를 호출하는 경우가 생긴다. (런타임 타입체크를 하지 않는게 비용이 싸기 때문) <br/>
자식 객체의 인스턴스는 자식객체의 소멸자가 먼저 호출되고 부모객체의 소멸자가 호출되어야 하므로 <br/>
vtable을 참조할 수 있도록 부모클래스의 소멸자를 virtual로 명시하여 상속가능성을 알려야한다.

```cpp
class A
{
public:
	A() { std::cout << "A Con\n"; }
	~A() { std::cout << "A Des\n"; }
};

class B : public A
{
public:
	B() { std::cout << "B Con\n"; }
	~B() { std::cout << "B Des\n"; }
};

int main()
{
	B* pB = new B();
	A* pA = pB;

	delete pA;

	return 0;
}
```
결과:
```
A Con
B Con
A Des
```
