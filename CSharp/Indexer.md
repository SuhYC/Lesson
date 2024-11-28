## Indexer (인덱서)
인덱스를 사용해 객체 내 데이터에 접근하게 해주는 프로퍼티. <br/>
```cs
class MyList
{
  private int[] array;
  public MyList()
  {
    array = new int[3];
  }

  public int this[int index] // 한정자 형식 this[형식 valuename]
  {
    get
    {
      return array[index];
    }
    set
    {
      if(index >= array.Length) // out of range!
      {
        Array.Resize<int>(ref array, index + 1); // 크기 조정
      }
      array[index] = value;
    }
  }
}
```
