# std::string
## 타입 앨리어스

다음 두 문장은 같다.

    std::string str;
    std::basic_string<char> str;

이는 std::basic_string<char> 형태가 사용할 일이 많기 때문에 다음과 같이 타입앨리어스를 제공하는 것이다.

    using string = basic_string<char>;

std::basic_string\<T\> 템플릿 클래스는 T타입의 문자로 구성된 문자열과 관련된 클래스이다. <br/>
흔히 char로 구성된 문자열을 사용할 일이 많으니 string이라는 간결한 표현을 사용할 수 있게 해둔 것이다. <br/>

[C# string과 비교](https://github.com/SuhYC/Lesson/blob/main/CSharp/string.md)
