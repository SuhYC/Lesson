# RSA 암호화
## 비대칭키 암호화

모듈러 상의 소인수 분해가 어려움을 이용한 암호화방식.<br/>
비대칭키 암호화이기 때문에 개인키와 공개키를 이용한 암호 $\cdot$ 복호화를 사용한다.<br/>

## 키 생성
1. 두개의 충분히 큰 소수 ```p```와 ```q```를 선택합니다.
2. ```p```와 ```q```로부터 모듈러스 $n = p \times q$를 얻습니다.
3. 오일러 피함수 $\phi(n) = (p - 1) \times (q - 1)$를 얻습니다.
4. 오일러 피함수로부터 서로소인 수 ```e```를 $1 < e < \phi(n)$ 범위에서 구합니다.
5. 오일러 피함수 모듈러 상에서 ```e```의 모듈러 역수 ```d```를 구합니다. $e \times d \equiv 1$ $mod$ $\phi(n)$
6. ```e```와 ```n```을 공개키로 전파합니다. 암호화는 문자데이터 ```m```에 대해 $c = m ^ e$ $mod$ $n$과 같이 진행합니다.
7. ```d```와 ```n```을 개인키로 저장합니다. 복호화는 암호데이터 ```c```에 대해 $m = c ^ d$ $mod$ $n$과 같이 진행합니다.

개인키 d는 외부로 공개되면 안됩니다.

## 사용되는 원리
### 1. 암호화, 복호화의 원리
먼저 암호문 $C$는 평문 $m$에 대해 $m^e$ $mod$ $n$으로 정의됩니다.<br/>
그러면 $C^d$는 $m^{e \times d}$ $mod$ $n$으로 전개됩니다. <br/>
이 때, $e \times d \equiv 1$ $mod$ $\phi(n)$ 로부터, $e \times d = k \times \phi(n) + 1$과 같이 사용할 수 있습니다.<br/>
그러면 $C^d = m^{k \times \phi(n) + 1}$ $mod$ $n$과 같이 전개할 수 있으며<br/>
$C^d = m \times m^{k \times \phi(n)}$ $mod$ $n$로 정리할 수 있습니다.<br/>
이 때, ```m```과 ```n```이 서로소인 경우와 서로소가 아닌 경우로 구분하여 설명하면,<br/>

#### ```m```과 ```n```이 서로소인 경우
페르마의 일반화된 소정리에 의해 ```a```와 ```n```이 서로소라면, $a^{\phi(n)} \equiv 1$ $mod$ $n$입니다.<br/>
그렇다면 위에 마지막으로 정리된 식을 $C^d = m \times m^{\phi(n)^k} = m \times 1^{k}$ $mod$ $n$과 같이 간단히 정리되어, <br/>
$C^d = m$ $mod$ $n$으로 최종 정리됩니다.

#### ```m```과 ```n```이 서로소가 아닌 경우
이 경우 복잡한 논리를 전개해야 하는데, 여기서 사용할 식은 페르마의 소정리이다.(위에 나온 일반화된 소정리와는 조금 다르다.) <br/>
페르마의 소정리란, 소수```p```에 대해, 어떤 정수```a```가 ```p```의 배수가 아니면, $a^{p-1} \equiv 1$ $mod$ $p$라는 정리이다.<br/>
위에 정리했던 식 $C^d = m \times m^{k \times \phi(n)}$ $mod$ $n$로부터 다시 출발하자.<br/>

$\phi(n) = (p - 1)(q - 1)$를 대입하면, $C^d = m \times m^{k \times (p - 1)(q - 1)}$ $mod$ $n$가 된다.<br/>
페르마의 소정리를 사용하여 2가지를 확인할 건데, 이는 ```p```모듈러 상에서 $m^{(p - 1)} \equiv 1$ $mod$ $p$와, $m^{(q - 1)} \equiv 1$ $mod$ $q$이다.<br/>
먼저 가정으로 충분히 큰 소수 ```p```와 ```q```를 가지고 시작하였기 때문에 $m < p, m < q$이다. ```p```와 ```q```보다 작은 수인 ```m```은 ```p```와 ```q```의 배수가 될 수 없다.<br/>
그러므로 페르마의 소정리의 조건을 만족한다.<br/>

결과적으로 $m \times m^{k \times (p - 1)(q - 1)}$ $mod$ $p$는 $m \times 1^{k \times (q - 1)}$ $mod$ $p$로 정리되어, $m \times m^{k \times (p - 1)(q - 1)}$ $mod$ $p$ $\equiv$ $m$ $mod$ $p$.<br/>
방금까지의 정리를 통해 $m \times m^{k \times (p - 1)(q - 1)} - m$ $\equiv$ $0$ $mod$ $p$임을 이끌어 내었고,<br/>
다시말하면 $m \times m^{k \times (p - 1)(q - 1)} - m$는 ```p```로 나누어 떨어짐을 의미한다.<br/>
이를 ```q```에 대해 다시 한번 계산하면 마찬가지로 $m \times m^{k \times (p - 1)(q - 1)} - m$는 ```q```로 나누어 떨어짐을 의미하게 되며,<br/>
이는 곧 $n = p \times q$에 대해서도 나누어 떨어짐을 의미한다.<br/>

결론 : $m \times m^{k \times (p - 1)(q - 1)} - m$는 ```n```에 대해서도 나누어 떨어진다.<br/>
-> $m \times m^{k \times (p - 1)(q - 1)} - m$ $\equiv$ $0$ $mod$ $n$.<br/>
-> $m \times m^{k \times (p - 1)(q - 1)} = m \times m^{k \times \phi(n)} = C^d$ $\equiv$ $m$ $mod$ $n$

### 2. 강력한 이유
먼저, ```n```과 ```e```로부터 복호화키 ```d```를 알아내기 위해서는 $\phi(n)$을 알아내야하고, 이는 곧 ```p```와 ```q```로 소인수분해에 성공해야한다는 것이다.<br/>
그런데, ```n```으로부터 ```p```와 ```q```를 구하기 위해서는 일반적인 브루트포스를 통해서는 $O(\sqrt{n})$의 시간이 걸린다.<br/> 
일반적으로 매우 큰 소수를 사용하기 때문에 이는 매우 비효율적인 공격이다.<br/>
GNFS라는 알고리즘으로 큰 수를 소인수분해할 수 있다고 하는데, 이 또한 수 일은 충분히 소요한다고 한다.<br/>
(추후 GNFS에 대해서도 알아보고 기록할 예정.)

## RSA와 함께 사용하면 좋은 알고리즘
$m^e$를 사용해서 암호화, $C^d$를 사용해서 복호화를 진행한다. 이는 일반적인 거듭제곱을 사용하면 상당히 오랜 시간이 걸린다.<br/>
이 때, [모듈러 지수법](https://github.com/SuhYC/Lesson/blob/main/Algorithm/%EB%AA%A8%EB%93%88%EB%9F%AC%EC%A7%80%EC%88%98%EB%B2%95.md)을 사용하여 거듭제곱을 보다 빠르게 계산할 수 있다.

## 서명
일반적으로 비대칭키 암호화에서 암호화```C(x)```와 복호화```D(x)```는 ```D(C(m)) = m```의 관계가 성립해야하지만,<br/>
```C(D(m)) = m```이 성립하는 것은 옵션이다.<br/>
그런데 이 옵션이 성립하게 되면, 개인키로 암호화하고, 공개키로 복호화하여 해당 메시지가 개인키를 소지한 사람이 암호화하였음을 인증할 수 있다.<br/>
RSA는 해당 옵션을 만족하며, 이를 통해 부인방지의 효과를 얻을 수 있다.