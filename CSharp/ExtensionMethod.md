# 확장 메소드
기존 클래스의 기능을 확장하는 기법. <br/>
최상단 정적 클래스에 메소드를 만들되, ```static```한정자로 수식하고, <br/>
첫번째 매개변수를 ```this```키워드와 함께 확장하려는 클래스(형식)의 인스턴스를 주면 된다. <br/>
이후 따라오는 매개변수 목록을 실제 확장 메소드를 호출할 때 입력되는 매개변수를 적으면 된다. <br/>

```cs
 public static class IntegerExtension // 최상단에 있어야하고 static 클래스여야한다!
 {
     public static int Power(this int myInt, int exp) // static 메소드면서 this로 클래스,형식을 지정해주어야한다!
     {
         int result = 1;
         for(int i = 0; i < exp; i++)
         {
             result *= myInt;
         }

         return result;
     }
 }
 internal class MainApp
 {

     static void Main()
     {
         int a = 5;
         Console.WriteLine(a.Power(5)); // 호출은 해당 클래스,형식의 변수에서 메소드를 호출하면 된다!
     }
 }
```
