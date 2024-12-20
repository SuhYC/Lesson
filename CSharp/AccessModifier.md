# 접근한정자
클래스 내의 필드, 메소드, 프로퍼티 등 모든 요소에 대해 은닉정도를 정할 수 있게 해주는 키워드. <br/>
명시적으로 지정하지 않은 접근한정자는 private으로 기본설정된다.

1. ```public```
- 클래스 내/외부 모든 곳에서 접근할 수 있다.
2. ```protected```
- 클래스의 외부에서는 접근할 수 없지만 파생 클래스에서는 접근할 수 있다.
3. ```private```
- 클래스의 내부에서만 접근할 수 있다.
4. ```internal```
- 같은 어셈블리에 있는 코드에서만 ```public```으로 접근할 수 있다.
- 다른 어셈블리에서는 ```private```과 같은 수준의 접근성을 가진다.
5. ```protected internal```
- 같은 어셈블리에 있는 코드에서만 ```protected```로 접근할 수 있다.
- 다른 어셈블리에서는 ```private```과 같은 수준의 접근성을 가진다.
6. ```private protected```
- 같은 어셈블리에 있는 클래스에서 상속받은 클래스 내부에서만 접근할 수 있다.
