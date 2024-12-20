# 연산자 오버로딩
클래스 내에서 다양한 연산자를 오버로딩하여 해당 클래스의 인스턴스에 맞게 연산자를 재정의할 수 있다.

## 산술연산자
해당 인스턴스에 산술연산자를 사용했을 때 동작을 재정의할 수 있다. <br/>
- ```return_type operator+(param)``` : + 연산자
- ```return_type operator-(param)``` : - 연산자
- ```return_type operator*(param)``` : * 연산자
- ```return_type operator/(param)``` : / 연산자
- ```return_type operator%(param)``` : % 연산자

## 증감연산자
해당 인스턴스에 증감연산자를 사용했을 때 동작을 재정의할 수 있다. <br/>
후위연산자의 매개변수에 붙는 int는 실제로 사용되지는 않지만 함수 시그니처에 필요하다. <br/>
- ```return_type operator++()``` : ++ 연산자 (전위);```++obj```
- ```return_type operator--()``` : -- 연산자 (전위);```--obj```
- ```return_type operator++(int)``` : ++ 연산자 (후위);```obj++```
- ```return_type operator--(int)``` : -- 연산자 (후위);```obj--```

## 대입연산자
해당 인스턴스에 대입연산자를 사용했을 때 동작을 재정의할 수 있다. <br/>
- ```return_type operator=(param)``` : = 연산자
- ```return_type operator+=(param)``` : += 연산자
- ```return_type operator-=(param)``` : -= 연산자
- ```return_type operator*=(param)``` : *= 연산자
- ```return_type operator/=(param)``` : /=연산자
- ```return_type operator%=(param)``` : %=연산자

#### 주의사항
1. 대입연산자는 (*this)의 참조자를 반환하는 방식으로 구현하여야한다.
2. ```operator=```에서는 자기대입에 대한 처리를 하여야한다.
3. ```operator=```로 복사하는 경우 객체의 모든 부분을 빠짐없이 복사하여야한다.

## 부호연산자
해당 인스턴스에 부호연산자를 사용했을 때 동작을 재정의할 수 있다. <br/>
산술연산자의 -연산자와 구분되는 점은 매개변수가 없다는 것. <br/>
- ```return_type operator-()``` : -연산자;```-obj```

## 접근연산자
해당 인스턴스에 접근연산자를 사용했을 때 동작을 재정의할 수 있다. <br/>
- ```return_type operator[](int index)``` : []연산자

## 부울연산자
해당 인스턴스로 조건연산에 사용할 때의 동작을 재정의할 수 있다. <br/>
- ```operator bool(param)``` : bool연산자; ```if(obj)```
- ```bool operator!(param)``` : !연산자; ```if(!obj)```

## 비트연산자
해당 인스턴스에 비트연산자를 사용했을 때 동작을 재정의할 수 있다. <br/>
- ```return_type operator&(param)``` : &연산자 (bit AND)
- ```return_type operator|(param)``` : |연산자 (bit OR)
- ```return_type operator^(param)``` : ^연산자 (bit XOR)
- ```return_type operator~()``` : ~연산자 (bit NOT)
- ```return_type operator<<(int n)``` : <<연산자 (left shift)
- ```return_type operator>>(int n)``` : >>연산자 (right shift)

## 비교연산자
해당 인스턴스에 비교연산자를 사용했을 때 동작을 재정의할 수 있다. <br/>
- ```return_type operator==(param)``` : ==연산자
- ```return_type operator!=(param)``` : !=연산자
- ```return_type operator<(param)``` : <연산자
- ```return_type operator>(param)``` : >연산자
- ```return_type operator<=(param)``` : <=연산자
- ```return_type operator>=(param)``` : >=연산자

## 함수호출연산자
해당 인스턴스에 함수호출연산자를 사용했을 때 동작을 재정의할 수 있다. <br/>
- ```return_type operator()(param)``` : ()연산자;```obj(param)```
