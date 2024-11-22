# call by reference
C++의 ```&```와 유사하다. 매개변수에 사용하여 참조를 넘길 수 있다. <br/>

반환값에도 사용 가능하나 호출할 메소드 이름 앞에 ref를 적어주어야 참조로 반환한다.
```cs
public static ref int Get(ref int a)
{
    return ref a;  // 매개변수 a를 참조로 반환
}

static void Main()
{
    int value = 10;

    // Get 함수는 a의 참조를 반환
    ref int refValue = ref Get(ref value); // ref 위치 확인!

    Console.WriteLine(refValue);  // 출력: 10
    refValue = 100;  // ref로 반환된 참조 값을 수정

    Console.WriteLine(value);  // 출력: 100 (값이 변경됨)
}
```

## out
출력 전용 매개변수. ref와 다른 점은 해당 매개변수에 결과를 저장하지 않으면 컴파일러가 에러메시지를 출력한다는 점.
```cs
void Divide(int a, int b, out int quotient, out int remainder)
{
  quotient = a / b;
  remainder = a % b;
}
```
