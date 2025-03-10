# Data Type

## 정수
1. ```byte``` : 1바이트, 0~255 // byte형식은 ubyte가 아닌 byte가 부호없는 정수.
2. ```sbyte``` : 1바이트, -128~127
3. ```short``` : 2바이트, -32768~32767
4. ```ushort``` : 2바이트, 0~65535
5. ```int``` : 4바이트, -2147483648~2147483647
6. ```uint``` : 4바이트, 0~4294967295
7. ```long``` : 8바이트, -9223372036854775808~9223372036854775807 // C++의 long은 4바이트, long long이 8바이트
8. ```ulong``` : 8바이트, 0~18446744073709551615
9. ```char``` : 2바이트, 유니코드 문자 // C++은 ASCII 및 확장 ASCII를 쓰는 것이 다름. C#의 char는 정수형으로 암묵적 변환되지 않음.

## 실수
1. ```float``` : 4바이트
2. ```double``` : 8바이트
3. ```decimal``` : 16바이트

## 문자와 문자열
1. ```char``` : 2바이트 문자
2. ```string``` : 문자열
```string```에 ```""" ... """```처럼 큰따옴표를 세개 붙여쓰면 이스케이프 문자 도움 없이 여러줄의 문자열을 만들 수 있다.

## 논리 형식
1. ```bool``` : 1바이트 <br/>
[왜 bool형 데이터는 1비트가 아닌 1바이트를 차지하나요?](https://github.com/SuhYC/Lesson/blob/main/C%2B%2B/vector.md)

## Object 형식
참조형식이기 때문에 힙에 데이터를 할당. 데이터를 힙에 할당한 후, ```object```는 해당 주소를 가리킨다.

## 상수형
```const int FIELD_NAME = 1;```

## 열거형
```enum ENUM_NAME : typename {EXNAME1, EXNAME2, EXNAME3}``` <br/>
typename은 생략 가능하다.(생략 시 int형 enum이 된다.) EXNAME1 = 3, 과 같이 작성한다면 이후 enum은 4, 5... 와 같이 매핑된다.

## Nullable
```typename? FIELD_NAME = null;``` <br/>
기본적으로 HasValue 때문에 1바이트가 추가되지만 메모리정렬 때문에 1바이트 이상 차지할 수 있다.

## var
약한 형식 검사를 통해 컴파일러가 자동으로 변수의 형식을 지정해준다. <br/>
단, 선언과 동시에 초기화하여야하며, 지역변수로만 사용할 수 있다.
