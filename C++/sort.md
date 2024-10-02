# sort()
C++ STL에 포함된 sort함수는 ```Intro Sort```를 사용한다.

### Intro Sort
작은 입력에 대해서는 ```Insertion Sort```를 사용하고, <br/>
일반적인 입력에 대해서는 ```Quick Sort```를 사용하고, <br/>
```Quick Sort```로 처리하기 어려운 케이스의 경우는 ```Heap Sort```를 사용한다.

작은 입력이란, 16이하를 의미하며 <br/>
```Quick Sort```의 재귀호출 깊이가 2⌈log⁡n ⌉를 넘어가게 되면 해당 부분에서 16이상의 길이를 가진 리스트에 대해 Heap Sort를 사용한다.

## list
sort함수의 매개변수로는 ```RandomAccessIterator```타입의 반복자를 사용하여야 한다. <br/>
하지만 list의 반복자는 ```BidirectionalIterator```타입이다. <br/>
list를 정렬하기 위해서는 list 내부에 따로 구현되어 있는 sort함수를 사용하여야한다. <br/>
이 경우는 ```Merge Sort```를 사용한다.
