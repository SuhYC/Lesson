# Dangling Pointer
## 댕글링 포인터

포인터는 기본적으로 어떤 주소를 가리키고 있는 것이다. <br/>
하지만 앞뒤 문맥없이 포인터만 보고는 포인터가 가리키는 주소가 할당되어있는 메모리인지 할당되어있지 않은 메모리인지 알 방법은 없다. <br/>
이미 해제한 메모리를 접근하여 다른 동작을 수행하려고 하면 치명적인 에러가 발생할 수 있다.

### 대처법
항상 메모리를 해제할 땐 포인터가 다시 nullptr로 설정될 수 있도록 하자. <br/>
하지만 이 방법도 동시에 두 개 이상의 포인터가 같은 주소를 가리키고 있던 상황에서 해제하고 하나를 nullptr로 설정한 경우에는 남은 한 포인터가 문제가 될 수 있다. <br/>
(그런 당신을 위해 준비한 스마트포인터!)