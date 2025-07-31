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

## 전역객체는 언제 소멸되는데?
결론부터 말하면 전역객체는 생성된 순서의 역순으로 소멸한다. <br/>
다음 코드로 4가지 케이스를 구분하여 소멸자에서 출력하는 예제를 만들어보았다. <br/>
1. 전역에 선언된 객체
2. 클래스 멤버로 선언된 static 객체
3. 클래스 멤버함수 내에 선언된 static 객체 (Meyers Singleton)
4. 메인함수 내에 선언된 객체

```cpp
#include <iostream>

class Global
{
public:
	~Global()
	{
		std::cout << "Global\n";
		return;
	}
};

class StaticLocal
{
public:
	~StaticLocal()
	{
		std::cout << "Static Local\n";
		return;
	}
};

class StaticMember
{
public:
	~StaticMember()
	{
		std::cout << "Static Member\n";
		return;
	}
};

class MainLocal
{
public:
	~MainLocal()
	{
		std::cout << "Main Local\n";
		return;
	}
};

class Test
{
public:
	static StaticMember sm1;
	static StaticMember sm2;
	void Prepare()
	{
		static StaticLocal sl;
		return;
	}
};

StaticMember Test::sm1{};

Global g;

//StaticMember Test::sm2{};

int main()
{
	MainLocal ml;

	Test t;
	t.Prepare();

	return 0;
}
```

4가지 모두 프로그램의 종료를 기점으로 소멸하는 객체이다. <br/>
하지만 일반적인 케이스에서 이 중에 1가지를 제외하고는 그 소멸 순서를 예측할 수 없다. <br/>

일단 예제코드에서는 <br/>
1. 메인로컬
2. 스태틱로컬
3. 글로벌
4. 스태틱멤버
의 순서로 소멸한다. <br/>

그 이유는 메인로컬의 경우는 프로그램의 종료가 기점일 뿐 전역객체가 아니다. <br/>
결국 스코프 내에 존재하므로 스택에 선언된 객체이며, 스택이 먼저 정리되어야하므로 메인로컬은 무조건 저 4가지 중 가장 빠르게 소멸한다. <br/>

그리고 나머지 3가지 케이스는 초기화된 순서의 역순으로 소멸하는 셈이다. <br/>

#### 어? 그러면 소멸 순서를 예측할 수 없다는 말은 틀린거 아닌가요?
코드를 소스파일 하나만으로 작성하는 경우는 예측할 수 있다. <br/>
하지만 우리는 수많은 소스파일과 헤더파일로 프로젝트를 구성하는게 효율적이라는 것을 알고 있다. <br/>
프로젝트의 규모가 커지면 반드시 여러개의 파일로 프로젝트를 구성하게 된다. <br/>
이 때 [컴파일 과정](https://github.com/SuhYC/Lesson/blob/main/C%2B%2B/Compile_Process.md)중 3단계에서 cpp파일이 오브젝트파일로 번역되고, 4단계에서 오브젝트 파일들을 병합하여 하나의 실행파일로 만들게 되는데, <br/>
이 때 오브젝트파일의 순서는 보장되지 않는다. <br/>

예제코드는 하나의 cpp파일에 모든 코드가 있기 때문에 순서를 예측할 수 있었지만 <br/>
여러개의 번역단위를 갖는 프로젝트에서는 순서를 예측할 수 없다. <br/>

싱글턴객체가 서로를 참조하면 문제가 생길 수 있는 이유이기도 하다. <br/>
싱글턴객체 중에 어떤게 먼저 생성되고 어떤게 먼저 소멸할 지 모르기 때문에 싱글턴 객체가 서로를 참조하는 경우는 배제하는게 좋다.
