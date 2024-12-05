# 대리자
메소드에 대한 참조이다. <br/>
참조할 메소드의 반환 형식과 매개변수를 명시하여야한다. <br/>
대리자는 인스턴스가 아닌 형식이기 때문에 메소드를 실제로 참조할 수 있도록 하려면 대리자를 통해 인스턴스를 따로 만들어야한다. <br/>
```cs
delegate int MyDelegate(int a, int b); // 대리자 선언!

int Plus(int a, int b)
{
  return a + b;
}

MyDelegate Callback;
Callback = new MyDelegate(Plus); // 인스턴스 생성!
Console.WriteLine(Callback(3,4)); // 7 출력
```

## 어디에 사용할까?
대리자는 형식이라고 했다. <br/>
그러므로 어떤 함수에서 해당 대리자를 파라미터로 받을 수 있다. <br/>
파라미터로 받은 대리자를 이용해 함수 내에서 어떤 로직을 수행한 후 대리자에 저장해둔 함수 참조를 실행하는 것이다. <br/>

```cs
delegate int Compare(int a, int b); // 1. 대리자 선언!

static int AscendCompare(int a, int b) // 2. 대리자로 참조할 실제 함수 작성!
{
  if (a > b)
  {
    return 1;
  }
  else if (a == b)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

static void BubbleSort(int[] DataSet, Compare Comparer) // 3. 대리자를 파라미터로 받는 함수 작성!
{
  int i = 0;
  int j = 0;
  int tmp = 0;
  for (i = 0; i < DataSet.Length - 1; i++)
  {
    for (j = 0; j < DataSet.Length - (i + 1); j++)
    {
      if (Comparer(DataSet[j], DataSet[j + 1]) > 0) // 대리자 파라미터를 통한 함수 참조!
      {
        tmp = DataSet[j + 1];
        DataSet[j + 1] = DataSet[j];
        DataSet[j] = tmp;
      }
    }
  }
}

int[] array = {3, 7, 4, 2, 10};
BubbleSort(array, new Compare(AscendCompare)); // 4. 함수 사용!
```

## 일반화 대리자
대리자도 일반화가 가능하다. <br/>
```cs
delegate int Compare<T>(T a, T b);
```
이후 사용에는 당연히 타입을 구체화해서 쓰면 된다.

## 대리자 체인
대리자 하나가 메소드 여러 개를 동시에 참조할 수 있다. <br/>
```+=```연산자를 통해 추가할 참조를 결합할 수 있다. (인스턴스 선언에는 ```=```연산자를 사용해야한다.) <br/>
```cs
delegate void ThereIsAFire(string location);

void Call119(string location)
{
    Console.WriteLine("소방서죠? 불났어요! 주소는 {0}", location);
}

void ShoutOut(string location)
{
    Console.WriteLine("피하세요! {0}에 불이 났어요!", location);
}

void Escape(string location)
{
    Console.WriteLine("{0}에서 나갑시다!", location);
}

ThereIsAFire Fire = new ThereIsAFire(Call119); // 인스턴스 선언이기에 +=가 아닌 =를 사용한다.
Fire += new ThereIsAFire(ShoutOut); // 추가 참조를 결합하기 위해 +=를 사용한다.
Fire += new ThereIsAFire(Escape);

Fire("우리 집"); // Call119("우리 집"); ShoutOut("우리 집"); Escape("우리 집");이 순서대로 실행된다.
```

다음과 같이 결합하는 것도 가능하다. <br/>
```cs
ThereIsAFire Fire = new ThereIsAFire(Call119) + new ThereIsAFire(ShoutOut) + new ThereIsAFire(Escape);
```
```cs
ThereIsAFire Fire = (ThereIsAFire) Delegate.Combine(new ThereIsAFire(Call119), new ThereIsAFire(ShoutOut), new ThereIsAFire(Escape));
```

결합을 끊는건 ```-=```연산자나 ```-```연산자, ```=```연산자, 또는 Delegate.Remove()메소드를 통해 가능하다.


## 익명 메소드
함수명이 없는 함수도 만들어 참조할 수 있다. <br/>
이 때, 익명메소드는 자신을 참조할 대리자의 형식과 동일한 형식으로 선언되어야한다. <br/>
```cs
delegate int Calculate(int a, int b);

Calculate Calc;
Calc = delegate (int a, int b) { return a + b; }; // 익명 메소드!
```

## event
이벤트는 대리자에 event 키워드로 수식하여 만든다. <br/>
일반적인 대리자는 ```public```이나 ```internal```로 수식되어 있으면 클래스 외부에서 호출이 가능하다. <br/>
하지만 이벤트는 ```public```한정자로 선언되어 있어도 자신이 선언된 클래스 외부에서는 호출이 불가능하다. <br/>
대리자는 콜백의 용도로 사용해야하고, 이벤트는 객체의 상태 변화나 사건의 발생을 알리는 용도로 구분해서 사용해야한다.
