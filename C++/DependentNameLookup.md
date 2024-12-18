# 지연된 이름 해석 문제
템플릿 코드에서 이름을 해석할 때, 템플릿 인자에 의존적인 이름을 해석하려고 하면 발생할 수 있는 문제이다. <br/>
```typename``` 키워드를 통해 해결할 수 있다.
```cpp
template<typename T>
void foo(const T& param)
{
  // T::const_iterator* x; // T::const_iterator가 뭔데!! T::const_iterator랑 x랑 곱하라는 거냐??
  typename T::const_iterator* x; // T::const_iterator 가 타입이구나! T::const_iterator타입의 포인터를 만드는 거군!
}
```

## 뭐하다 알게 되었니
```std::unordered_map```과 ```std::unordered_multimap```을 원하는 기능으로 사용하려고 ```WrapperClass```를 만들다가 [발견](https://github.com/SuhYC/RPGServer/blob/main/RPGServer/UMapWrapper.hpp). <br/>
```std::unordered_multimap<T1, T2>::iterator``` 부분에서 발생했다. <br/>
```typename```키워드를 통해 해결.
