# Standard Template Library
## 표준 템플릿 라이브러리
템플릿을 사용해 타입을 일반화하여 제공하는 표준 라이브러리.

## 컨테이너
### 시퀀스 컨테이너
정해진 규칙 없이 데이터를 저장하는 컨테이너.
1. ```std::vector<T>```
2. ```std::list<T>```
3. ```std::deque<T>```
### 연관 컨테이너
일정한 규칙에 따라 데이터를 조직화하여 저장하는 컨테이너.
1. ```std::set<T>```
2. ```std::map<TKey, TValue>```
3. ```std::multiset<T>```
4. ```std::multimap<TKey, TValue>```
5. ```std::unordered_set<T>```
6. ```std::unordered_map<TKey, TValue>```
7. ```std::unordered_multiset<T>```
8. ```std::unordered_multimap<TKey, TValue>```
### 컨테이너 어댑터
```std::stack<T>```과 ```std::queue<T>```, ```std::priority_queue<T>```는 ```컨테이너 어댑터```로, <br/>
기본적인 컨테이너에 특정한 인터페이스 그 기능을 제한하여 구현되어 있다.

## 알고리즘
1. ```std::sort```
정렬한다. 단, 동일한 데이터들에 대해 순서가 바뀔 수 있다.
2. ```std::stable_sort```
정렬한다. 단, 동일한 데이터들에 대해 순서를 유지한다.
3. ```std::unique```
중복된 원소를 후위로 배치하고 중복이 제거된 원소들 중 마지막 원소의 다음 반복자를 리턴한다.<br/>
erase와 함께 사용하여 중복을 제거할 수 있다.

## 주의사항
1. **```size()```는 O(1)을 보장하지 않을 수 있다.** <br/>
```std::vector<T>::size()```는 O(1)을 보장하지만, ```std::list<T>::size()```는 O(N)의 복잡도를 가질 수 다. <br/>
원소가 없음을 확인하기 위해서는 ```std::list<T>```의 경우, ```std::list<T>::size() == 0```보다 ```std::list<T>::empty()```를 쓰는 것이 좋다.

2. **```std::vector<bool>```은 ```std::vector<T>```와 다르게 동작한다.** <br/>
```std::vector<bool>```은 비트연산을 통해 구현되기 때문에 ```operator[]```또한 bool타입 데이터에 대한 접근이 아닌 비트필드에 대한 간접적 참조를 제공한다. <br/>
또한 비트연산 오버헤드가 추가되기 때문에 가급적 사용하지 않는 것이 좋다. ```std::bitset```을 사용하는 것도 방법.

3. **상속된 객체는 삽입하는 과정에서 기본클래스의 복사 생성자를 통해 복사되며 파생클래스의 정보를 잃어버릴 수 있다.** <br/>
해당 현상을 ```slice```문제라고도 하며, 이를 방지하기 위해서는 객체타입이 아닌 객체포인터타입으로 컨테이너를 만드는 방법이 있다. <br/>
객체를 복사하는 것이 아닌 포인터를 복사하기 때문에 ```slice```문제는 해결할 수 있다. <br/>
다만 객체포인터를 컨테이너에 담는 건 다른 부수적인 문제가 등장한다. <br/>
인스턴스를 사용이 끝난후 ```delete```해주어야한다는 점과 ```remove```함수를 사용하는데 있어 주의해야한다는 점이다. <br/>
위 두 문제는 스마트포인터를 컨테이너에 저장하는 것으로 [해결](https://github.com/SuhYC/Lesson/blob/main/C%2B%2B/Container_pop.md)이 가능하다.

4. **```auto_ptr```의 컨테이너는 만들지 말 것.** <br/>
```auto_ptr```는 복사를 허용하며, 이 경우 복사된 객체는 nullptr로 세팅되며 복사한 객체로 소유권이 복사된다. <br/>
STL의 컨테이너가 원하는 복사의 형태가 ```auto_ptr```의 복사와는 다르다.

5. **데이터를 삭제하는데 컨테이너마다 다른 방식을 쓴다.** <br/>
```std::vector<T>```, ```std::string```, ```std::deque<T>```는 erase-remove 합성문을 통해 <br/>
```Container.erase(std::remove(Container.begin(),Container.end(), 1234), Container.end()); // 1234를 모두 제거!```와 같이 사용할 수 있다. <br/>
```std::list<T>```는 ```std::list<T>::remove```를 사용한다. (erase-remove합성문도 쓸 수 있지만 멤버함수가 더 낫다) <br/>
표준연관컨테이너는 erase멤버함수를 사용한다. (remove 알고리즘을 사용하면 컨테이너의 후방으로 필요없는 데이터를 밀어버리므로 구조가 깨진다.)

6. **상등관계와 동등관계는 다르다.** <br/>
상등관계(x==y)와 동등관계(!(x<y)&&!(x>y))는 헷갈리기 쉽다. STL의 모든 연관 컨테이너는 내부데이터 관리에 동등관계를 사용한다. <br/>
연관 컨테이너는 2가지의 비교를 통해 기능을 구성한다. 첫번째는 정렬순서비교이며, 두번째는 같은값인지 판단하는 비교이다. <br/>
상등관계를 사용하면 정렬순서를 비교할 수 없게된다.

7. **포인터를 저장하는 연관컨테이너에는 별도의 적합한 비교함수를 정해주자.** <br/>
연관 컨테이너에서 중요한건 주소가 아니고 데이터이다.

8. **연관컨테이너용 비교함수는 같은 값에 대해 false를 반환해야한다.** <br/>
위에서 연관컨테이너에 동등관계 비교함수를 사용한다고 했다. 이 때 중복된 키 값을 어떻게 판단할까? <br/>
a와 b에 대해 !(a > b) && !(b > a)면 중복된 키가 된다. 여기서 > 부분에 원하는 비교함수를 넣는 것이다. <br/>
그런데 같은 값에 true가 반환되면 어떻게 될까? 결과는 false && false로 중복된 키를 가려낼 수 없게 된다. <br/>
마찬가지로 비교함수를 뒤집어 역순으로 정렬하려고 하는 경우에도, ```return !(a < b)```가 아닌 ```return b < a```를 비교함수로 넣어줘야한다.

9. **```std::set<T>```와 ```std::multi_set<T>```의 키를 수정하지 말아야 한다.** <br/>
당연히 정렬상태가 깨지고 예기치 않은 동작을 유도할 수 있다. <br/>
```cpp
std::set<int> s;
s.insert(2);
s.insert(3);
s.insert(1);

auto itr = s.find(3);
if (itr != s.end())
{
    const_cast<int &>(*itr) = 0; // 0으로 수정했으나 루트가 2, 왼쪽노드가 1, 오른쪽 노드가 0인 상태!
}

auto itr2 = s.find(0); // 0을 찾으려는데
if (itr2 != s.end()) // 루트가 2 -> 왼쪽노드 1 -> 단말노드 ??? 없네?
{
    std::cout << "Found!";
}
else
{
    std::cout << "??"; // 여기로 진입!
}
```

10. **빠른 검색을 위한 경우에도 조건을 따져보아야한다.** <br/>
일반적으로 가장 빠른 검색을 보장하는건 해시테이블기반의 컨테이너이다. <br/>
하지만 삽입/수정이 빈번한 경우 해시테이블기반의 컨테이너는 ```rehash```에 무너질 가능성이 크다. <br/>
게다가 많은 메모리를 사용하는 것은 덤 <br/>
그리고 다음으로 선정할 수 있는 컨테이너는 이진트리 기반 컨테이너이다. <br/>
이진트리 기반의 컨테이너는 접근, 삽입, 삭제에 모두 O(logN)의 시간복잡도를 갖는다. <br/>
그런데 만약 정렬된 상태를 보장할 수 있다면, ```std::vector<T>```를 사용해 이진탐색을 시도하는 것이 나을 수 있다. <br/>
그 이유는 단연코 메모리. 이진트리 기반 컨테이너에 비해 ```std::vector<T>```는 굉장히 적은 메모리를 차지하게 된다. <br/>
적은 메모리와 연속된 메모리를 사용하기에 ```page fault```도 줄어들게 된다.

11. **```std::map<TKey, TValue>```에 요소를 추가할 때는 ```operator[]```보다 ```insert```가 효율적이다.** <br/>
```operator[]```는 해당 키가 있는지 점검합니다. 없다면 해당 키```k```, 값타입의 기본생성자```v()```를 페어로 묶어 추가합니다. <br/>
이 때, ```operator[]```는 ```std::map```에 지정된 값 타입의 기본 생성자를 사용해 페어를 만들고, 해당 객체의 참조자를 반환하며, <br/>
해당 참조자를 대입연산자를 호출해 삽입하게 된다. <br/>
```cpp
// operator[]가 요소 추가에 사용된 경우
std::map<TKey, TValue> m;
std::pair<std::map<TKey,TValue>::iterator, bool> result = m.insert(std::map<TKey, TValue>::value_type(key, TValue()); // 없으니 추가!
result.first->second = value; // 값만 수정!
```
하지만 ```insert```는 기본생성자와 대입연산자 없이 똑같은 작업을 수행한다. <br/>
반대로 저장된 요소에 갱신하는 경우는 ```operator[]```가 효율적이다. <br/>
이미 해당 키에 대한 객체가 있기 때문에 객체를 소멸시키는 과정이 필연적으로 따라오기 때문.