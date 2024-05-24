# auto Keyword
## auto 타입

이후 지정될 타입을 컴파일시간에 추론하여 변수 앞에 붙인다.   
복잡한 타입명을 지정한 경우 쉽게 처리할 수 있다.   

### auto&
auto는 레퍼런스와 const가 제거된다.   
불필요한 복제가 발생할 수 있으니  auto&가 사용된다.

### auto*
auto로도 물론 포인터를 받을 수 있다.   
auto&의 케이스처럼 복제가 일어나는 경우도 없다.   
auto*의 목적은 포인터임을 명시적으로 나타내기 위해서이다.   

또한 const와 auto가 같이 있을 때 이상한 동작을 수행하는 것을 막기 위해서도 쓰인다.   
const auto와 auto const는 둘 다 [포인터상수](https://github.com/SuhYC/Lesson/blob/main/C%2B%2B/%EC%83%81%EC%88%98%ED%8F%AC%EC%9D%B8%ED%84%B0%2C%ED%8F%AC%EC%9D%B8%ED%84%B0%EC%83%81%EC%88%98.md)를 의미하게 된다.   
그러므로 상수포인터를 의도한 것이라면, const auto* 를 사용하는 것이 바람직하다.
