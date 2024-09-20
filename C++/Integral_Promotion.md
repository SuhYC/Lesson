# Integral Promotion
## 정수 승격
일반적으로 프로세서가 작업하기 가장 좋은 크기의 정수형 데이터를 ```int```형으로 정의한다.<br/>
그런 의미에서 작은 정수형 데이터는 ```int``` 또는 ```unsigned int```로 변환하여 계산하는 것이 효율적일 수 있다.<br/>

## 주의사항
작업환경에 따라 ```int```로 promotion할 지, ```unsigned int```로 promotion할 지는 다르다.<br/>
어떤 형태로 promotion하는 지를 알아두어야 의도하지 않은 동작이 발생하지 않게할 수 있다.

```cpp
    unsigned char a = 0xff;
    unsigned long long b = a << 24; // (signed int)0xff00 0000
    
    // 0xff00 0000 == -16777216, to ull -> 0xffff ffff ff00 0000 (2의 보수 처리) -> 18446744073692774400(dec)
 ```
이 코드에서는 ```signed int```로 promotion하기 때문에 이러한 결과가 나온다.
