# 이름 맹글링
C++의 함수들은 함수 오버로딩이라는 것이 가능하다. <br/>
ex.
```cpp
void func(int); // _Z4funci
void func(double); // _Z4funcd
void func(int, int); // _Z4funcii
void add(int, int); // _Z3addii
```
```<_Z><함수명길이><함수명><매개변수정보>```로 정리된다. (컴파일러마다 다를 수 있다.) <br/>

단, 이러한 ```Name Mangling```은 C++에서 지원하는 기능이다. C언어는 지원하지 않는다. <br/>
그러므로 extern "C"{} 구문 내에서는 함수 오버로딩을 사용하면 안된다.
