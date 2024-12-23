# 프록시 패턴
객체의 대한 접근을 특정 클래스의 인스턴스를 거쳐 진행할 수 있도록 하는 패턴. <br/>
객체가 외부로 직접 노출되지 않도록한다.

## 유형
1. 가상 프록시(Virtual Proxy)
 - 객체가 실제로 필요할 때까지 객체의 생성 및 초기화를 지연시킴.
2. 리모트 프록시(Remote Proxy)
 - 원격시스템의 객체에 대한 접근을 처리.
3. 보호 프록시(Protective Proxy)
 - 객체에 대한 접근을 제어하여 권한이 있는 사용자만 접근하도록함
4. 캐시 프록시(Cache Proxy)
 - 객체의 데이터나 결과를 캐시하여 성능을 최적화하는데 사용

## 장점
1. 지연초기화를 통해 무거운 객체를 사용하는 시점까지 생성 및 초기화를 지연하여 성능을 최적화할 수 있다.
2. 사용자의 요청마다 객체를 생성하는 것이 아니라 접근을 제어하여 이미 생성된 객체를 재사용하도록 할 수 있다.
3. 필요한 권한을 검증하는 로직을 추가하여 보안수준을 올릴 수 있다.
4. 실제 객체에 대한 호출을 가로채어 요청과 응답에 대한 로그를 작성하여 모니터링을 수행할 수 있다.

## 단점
1. 프록시 객체에 접근하는 시간이 추가되므로 실제 객체를 도달하는데 추가적인 시간이 소요된다.
2. 시스템에 추가적인 계층이 생겨 복잡성이 증가한다.

## 가상프록시 예제
```cpp
class RealObject
{
public:
  void SomeMethod() { std::cout << "Hello, World!"; }
};

class Proxy
{
private:
  RealObject* m_obj;
public:
  Proxy() : m_obj(nullptr) {}

  void request()
  {
    if (!m_obj)
    {
      m_obj = new RealObject();
    }
    m_obj->SomeMethod();
  }

  ~Proxy()
  {
    delete m_obj;
  }
};

int main()
{
  Proxy proxy;
  proxy.request(); // m_obj에 새로운 객체를 생성하여 동작을 수행한다.
  proxy.request(); // 이미 생성되어 있던 객체를 사용하여 동작을 수행한다.

  return 0;
}
```
