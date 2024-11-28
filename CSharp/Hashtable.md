# 해시테이블
키와 값의 쌍으로 이루어진 데이터를 다룰 때 사용하는 해시기반 자료구조. <br/>
해시함수를 이용해 O(1)의 탐색속도를 갖는다. <br/>

## 예제
```cs
Hashtable ht = new Hashtable();
ht["book"] = "책";
ht["cook"] = "요리사";

Console.WriteLine(ht["book"]); // 요리사
```

## 원리
[링크](https://github.com/SuhYC/Lesson/blob/main/Data_Structure/Hashtable.md)

## 초기화
```Hashtable```도 초기자를 통한 초기화가 가능하다. <br/>
```cs
Hashtable ht = new Hashtable()
{
  {"key1", 1}, // ,로 구분하는거 주의!
  {"key2", 2},
  {"key3", 3}
}

Hashtable ht2 = new Hashtable()
{
  ["key1"] = 1,
  ["key2"] = 2,
  ["key3"] = 3
};
```
