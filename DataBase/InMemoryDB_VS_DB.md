# Redis 캐싱 사용 유무 비교
```In-Memory-DB```의 특성을 이해하고 나면 바로 연결되는 것이 하나 있다. <br/>
보조기억장치를 조회해야하는 전통적인 DB를 조회하는 횟수를 줄이고 ```In-Memory-DB```를 사용하여 캐싱을 하면 얼마나 빠를까? <br/>
간단한 실험환경을 구현해서 테스트해보자.

## 실험방법
1. MSSQL에 50개의 데이터를 삽입하고 조회할 수 있도록 한다.
 - MSSQL에 odbc로 연결할 서버는 C++로 작성한다.
2. Redis를 사용해 캐싱기능을 사용할 함수를 따로 작성한다. <br/>
```cpp
std::string GetCharListCache(const int userCode_)
{
	std::string ret;
	if (m_RedisManager.GetCharList(userCode_, ret)) // Redis확인
	{
		return ret;
	}

	ret = GetCharList(userCode_); // 전통적인 DB조회버전
	m_RedisManager.CreateCharList(userCode_, ret); // 캐시 남기기
  
	return ret;
}
```
3. 클라이언트에서 데이터를 10000회 요청한다. (매 회마다 50개의 데이터를 전송받는다고 생각하면 된다.)

## 결과
전통적인 DB조회 : 3648 3206 3179 3020 3297 <br/>
캐싱버전 : 2882 3002 2999 2700 3120 <br/>
전통 평균 : 3270 <br/>
캐싱 평균 : 2940

## 어찌보면 당연한 거 아니야?
꼭 당연하리란 법은 없기는 하다. <br/>
갑자기 이 테스트를 굳이 해 본 이유는 네트워크IO오버헤드 때문이다. <br/>
디스크 오버헤드가 큰 건 맞는데 네트워크오버헤드도 크기 때문에 캐시서버로 조회성능을 높이고 싶은 것이라면 동일한 장치에 구성하여야한다. <br/>
그리고 MSSQL - SQLServer도 어느정도 캐싱 기능을 제공하기 때문에 항상 ```In-Memory-DB```가 더 빠르다라고 이야기하기는 무리가 있다. <br/>
당장 몇번 더 시도했을 때 캐싱쪽에서도 데이터가 팍 튀는 경우가 있었다. (4000 초과하는 경우도..) <br/>
물론 전통적인 버전에서 쿼리를 수정하지 않고 동일한 쿼리로 계속 시도했기 때문에 실행계획이 재사용되었을 수 있다. 그래서 별 차이가 안났을지도. <br/>
그리고 굉장히 간단한 쿼리를 실험에 사용했다. 쿼리 동작이 복잡할 수록 캐싱이 유리해진다. <br/>
쿼리 부분은 SP를 쓸수도 있는거니까..

## 어떤 경우에 더 유리할까?
1. 쿼리의 결과를 DB에 저장하지 않으면서 쿼리의 동작이 복잡하여 실행이 오래걸릴 때
 - 이 경우 쿼리의 결과를 ```In-Memory-DB```에 저장한다면, 이후 쿼리 동작을 무시하고 결과만 받아올 수 있다.
2. 자주 변경되지 않는 데이터
 - 동기화가 중요한 데이터는 변경시마다 ```In-Memory-DB```와 전통DB를 모두 수정해주어야한다.
3. 읽기 동작 비율이 높은 데이터
 - 변경되지 않는 데이터와 비슷한 맥락 외에도, 전통DB 자체에 부여되는 읽기 부하를 줄일 수 있다.

## 어떤 경우에 불리할까?
1. 과도하게 큰 용량의 데이터
 - 메모리에 저장되기 때문에 그 한계가 명확하다. 메모리를 아끼려고 가상메모리로 보조기억장치까지 끌어다 쓰는 마당에..
2. 너무 자주 변경되는 데이터
 - 결국 전통DB도 수정해야되는데 ```In-Memory-DB```도 수정해야될 판.
 - 물론 이건 전통DB에 반영하는 것을 간헐적으로 구성하면 문제가 줄어든다. 다만, 서버다운에 매우 취약해진다.
