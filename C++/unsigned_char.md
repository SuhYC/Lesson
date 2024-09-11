# char vs unsigned char

char는 1바이트 데이터를 저장하는 자료형이다. <br/>
흔히 문자를 표기하는데 char형을 사용하기 때문에 문자 자료형이라고 생각하기 쉽지만, <br/>
char 또한 정수형 데이터이다. (다만 해당 정수가 %c 포맷에 의해 ascii와 매칭되어 출력될 뿐이다.) <br/>
그렇기에 unsigned char가 있는 것도 이상한 것은 아니다.

## unsigned char를 사용하는 이유?

간단하다. char는 음수를 포함하기 때문에 특정 작업을 하기 불편하다. <br/>
예를 들면 bit shifting이나 메모리접근. <br/>
특히 주소에는 음수를 사용하지 않기 때문에 메모리접근에는 unsigned 자료형을 사용하는 것이 낫다. <br/>
그리고 실사용은 char와 큰 차이는 없다. <br/>

    unsigned char a, b;
    a = 65; // 'A' in ascii
    b = 'A'; 
    std::cout << a << b;
    // 결과 : AA

주로 암호화에서 unsigned char로 변환하여 연산한다.

## 주의사항

컴파일러마다 char를 signed char로 쓸 지 unsigned char로 쓸 지는 다르다. <br/>
또한, 일반적으로 1바이트형 데이터를 사용할 때, 4바이트형으로 integral promotion할 수도 있다. 이 경우 signed int 형태로 연산이 들어갈 수 있다.

    unsigned char a = 0xff;
    unsigned long long b = a << 24; // (signed int)0xff00 0000
    
    // 0xff00 0000 == -16777216, to ull -> 0xffff ffff ff00 0000 (2의 보수 처리) -> 18446744073692774400(dec)
 
