# 싱글턴 패턴
클래스의 인스턴스를 하나만 생성하고, 이를 어디서나 접근할 수 있도록 보장하는 패턴. <br/>
전역적으로 단 하나의 인스턴스가 필요한 경우에 사용. <br/>
```cpp
class Singleton
{
private:
  static Singleton* instance;
  Singleton() {} // private 생성자로 다른 곳에서 생성못하게 한다!
public:
  static Singleton* getInstance()
  {
    if (instance == nullptr)
    {
      instance = new Singleton();
    }
    return instance;
  }
};
```

## 단점
과도한 싱글턴 패턴의 사용은 전역 변수의 증가나 다름없어 모듈성이 떨어지며 코드 간 의존성이 증가하고 테스트와 유지보수를 어렵게할 수 있다.

## 멀티스레드 상황에서 주의사항
위 예제코드에서 if문의 인스턴스가 없는지 확인하는 동작은 여러 스레드가 동시에 진행할 수 있다. <br/>
인스턴스가 없다고 판단한 스레드들이 동시에 if문을 진입하여 할당하고 싱글턴 객체에 덮어씌우는 동작을 수행하게 되면 메모리 누수가 발생할 수 있다. <br/>

이를 해결하기 위해 더블체크락킹을 사용할 수 있다. <br/>
```cpp
class Singleton
{
private:
  static Singleton* instance;
  static std::mutex mu; // 동기화를 위하여!
  Singleton() {} // private 생성자로 다른 곳에서 생성못하게 한다!
public:
  static Singleton* getInstance()
  {
    if (instance == nullptr)
    {
      std::lock_guard<std::mutex> guard(mu); // critical section!
      if (instance == nullptr) // 다시 한번 체크!
      {
        instance = new Singleton();
      }
    }
    return instance;
  }
};
```
뮤텍스를 통한 상호배제는 비용이 많이 들지만, 초기 실행시 인스턴스가 없을 때만 진입하므로 동기화비용을 절약할 수 있다. <br/>
인스턴스가 생성된 이후에는 if조건문 하나만 점검하는 코드로 변하는 것과 마찬가지다!
