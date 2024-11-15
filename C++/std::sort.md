# std::vector와 std::list의 정렬

```std::vector```는 ```ArrayList```로, 연속된 주소를 갖는 데이터들을 보관하는 컨테이너이며, <br/>
```std::list```는 ```LinkedList```로, 불연속적인 주소를 갖는 데이터들을 보관하는 컨테이너이다. <br/>

두 자료구조를 정렬하는 방법은 어떤게 효율적일까? <br/>

## std::vector
```cpp
#include <algorithm>
#include <vector>

int main()
{
  std::vector<int> vec;
  vec.push_back(3);
  vec.push_back(1);
  vec.push_back(2);

  std::sort(vec.begin(), vec.end());

  // 원하는 동작

  return 0;
}
```
위 코드처럼 반복자를 사용하여 std::sort에 넣고 정렬할 수 있다.

## std::list
```cpp
#include <list>

int main()
{
  std::list<int> myList;
  myList.push_back(3);
  myList.push_back(1);
  myList.push_back(2);

  myList.sort();

  // 원하는 동작

  return 0;
}
```
위 코드처럼 자체적으로 정렬함수를 가지고 있다.

### 왜 std::list는 정렬함수를 따로 가지고 있을까?
먼저 ```std::vector```와 ```std::list```의 특성을 이해하여야한다. <br/>
언급하였듯 ```std::vector```는 ```ArrayList```이고, ```std::list```는 ```LinkedList```이다. <br/>
```ArrayList```는 데이터를 직접 옮기며 정렬하는 것이 좋다. 하나의 큰 메모리를 할당하고, 해당 메모리에 여러개의 데이터를 데이터 크기에 맞게 위치시키는 방식으로 저장하기 때문이다. <br/>
```LinkedList```는 노드를 직접 옮기며 정렬하는 것이 좋다. 각각의 노드는 다음 노드를 가리키게 되는데, 이 연결고리만 분해한 후 재배열할 수 있기 때문이다. <br/>
그렇기 때문에 ```std::list```는 ```Merge_sort```를 정렬함수로 채택하며, ```std::vector```는 ```Intro_sort```를 정렬함수로 사용하게 된다. <br/>

### Intro Sort
```Quick_sort```, ```Heap_sort```, ```Insertion_sort```세 가지 방식의 정렬을 알맞게 사용하여 ```O(nlogn)```을 보장하는 제자리정렬알고리즘. <br/>
```Quick_sort```는 일반적인 경우 빠르게 정렬할 수 있지만, 최악의 케이스(이미 정렬된 경우, 중복된 데이터가 많은 경우 등 분할이 불균형적으로 발생하는 경우)에 ```O(n^2)```이 된다. <br/>
```Quick_sort```의 재귀깊이가 ```logn```을 초과할 때, ```heap_sort```로 전환된다. <br/>
```Heap_sort```는 최악의 경우에도 ```nlogn```을 유지하는 정렬이다. 하지만 포인터연산과 캐시히트 관련 부분에서 오버헤드가 있어 일반적인 경우에 ```Quick_sort```보다 느리다. <br/>
정렬할 파티션의 요소수가 16이하인 경우 ```Insertion_sort```를 사용한다. <br/>
```Insertion_sort```의 경우는 ```O(n^2)```이지만, 정렬할 요소의 수가 적은 경우에 매우 빠르게 동작한다는 점에서 채용된다.

### 제자리 정렬 알고리즘
데이터가 담긴 ```ArrayList```내에서 해결이 가능한 정렬. 추가적인 메모리가 필요하지 않다. ex.```Intro_sort```
### 외부 정렬 알고리즘
데이터가 담긴 ```ArrayList```외에 다른 메모리가 필요한 정렬. ex.```Merge_sort```
