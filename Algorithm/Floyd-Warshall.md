# Floyd-Warshall
## 플로이드 워셜 알고리즘
### 최단거리

각 정점에서 다른 정점으로 이동하는 최단거리를 구하는 알고리즘이다.<br/>
시간복잡도가 $O(n^3)$이기 때문에 비효율적이라고 볼 수도 있겠지만, n이 충분히 작은 상황에서 간단하게 구성할 수 있는 알고리즘이다.<br/>

## 원리
어떤 정점 s에서 시작해, 경유할 정점m을 거쳐, 도착하려는 정점 e로 가는 방법이,<br/>
기존에 계산했던 s에서 e로 가는 방법보다 빠르다면 ```distance[s][e]```를 갱신한다.<br/>
이 때 주의해야하는 점은, m에 대한 반복문을 가장 바깥에 두어야한다는 점이다.<br/>

```cpp
int v = 정점의 갯수;
for(int m = 0; m < v; m++)
{
  for(int s = 0; s < v; s++)
  {
    for(int e = 0; e < v; e++)
    {
      distance[s][e] = (distance[s][e] > distance[s][m] + distance[m][e]) ? distance[s][m] + distance[m][e] : distance[s][e];
    }
  }
}
```
