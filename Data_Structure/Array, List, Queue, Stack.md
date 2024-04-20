## Array
배열. 연속된 주소값을 갖는 동일한 데이터들의 집합으로 보면 되겠다.

## List
리스트. 동일한 데이터들의 집합이지만 Array와는 다르다.
Array는 연속된 주소값을 갖기 때문에 인덱스로 호출할 수 있으며 이는 O(1)의 복잡도를 갖는다
List는 연속된 주소값을 가지지 않기 때문에 n번째 데이터를 조회할 때 O(n)의 복잡도를 갖는다.
List는 다음 데이터의 주소를 가지고 있는 형태로 구현된다.
ArrayList와 LinkedList로도 구분하는데
ArrayList는 Array에 가변길이를 추가한 개념으로 보면 되며, 길이를 조정하는 메소드를 호출할 때, 새로운 데이터를 할당하며 복사한 후 기존의 데이터를 지우는 방식으로 Array를 구성한다.
LinkedList가 일반적으로 말하는 List에 가깝다.
C++ STL에는 Vector가 ArrayList, List가 LinkedList의 형태로 구현된 것이다.
Singly Linked List와 Doubly Linked List, Circular Linked List 등이 있다.
Singly Linked List는 단방향 연결리스트로 특정 노드는 자신의 앞 노드를 알 수 없다. 대신 주소가 차지하는 공간이 작다.
Doubly Linked List는 양방향 연결리스트로 자신의 앞 노드도 파악할 수 있으나 주소가 차지하는 공간이 크다.
Circular Linked List는 마지막 원소가 Head원소를 가리키게 하는 것으로 순환연결된다.

## Queue
큐. FIFO의 구조를 갖는 자료구조이다.
먼저 삽입한 데이터가 먼저 나오며
Array든 ArrayList든 LinkedList든 다 Queue를 구현하는데 사용할 수 있다.
Array로 구현하면 고정길이인게 단점이고 pop을 호출할때마다 데이터의 이동이 필요하거나 또는 특별한 로직이 필요하다(head를 가리키는 포인터라거나..)
ArrayList로 구현하면 Array로 구현한 것보다 가변길이라는 장점이 생긴다.
LinkedList로 구현하면 특별한 로직 없이 Head만 바꿔가며 구현할 수 있다. 다만 Circular Linked List나 Doubly Linked List가 적합하다. 뒤에서 삽입하고 앞에서 데이터를 꺼내기 때문..

## Stack
스택. LIFO의 구조를 갖는 자료구조이다.
나중에 삽입한 데이터가 먼저 나오며
큐와 마찬가지로 여러가지 구현방법이 있다.
큐와 달리 앞에서 삽입하고 앞에서 꺼내면 되서 Singly Linked List로도 쉽게 구현된다.
