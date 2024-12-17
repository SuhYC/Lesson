# 방문자 패턴
객체의 구조와 그 구조에서 수행되는 동작을 분리하여 구현하는 디자인패턴. <br/>

## 절차
1. visitor 인터페이스를 정의한다. 해당 인터페이스는 각각의 클래스에서 구현될 visit메소드를 정의한다.
```cpp
class Book;
class Music;
class Movie;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual int visit(Book& book_) = 0;
    virtual int visit(Music& music_) = 0;
    virtual int visit(Movie& movie_) = 0;
};
```
2. 각각의 클래스를 구현한다. 그리고 visitor인터페이스를 통한 동작을 수행할 수 있도록 메소드를 정의한다.
```cpp
class Goods
{
public:
    virtual ~Goods() = default;
    virtual int accept(Visitor& visitor_) = 0;
};

class Book : public Goods
{
private:
    int price;
public:
    Book(int price_) : price(price_) {}
    int getPrice() const { return price; }

    int accept(Visitor& visitor_) override
    {
        return visitor_.visit(*this);
    }
};

class Music : public Goods
{
private:
    int price;
public:
    Music(int price_) : price(price_) {}
    int getPrice() const { return price; }

    int accept(Visitor& visitor_) override
    {
        return visitor_.visit(*this);
    }
};

class Movie : public Goods
{
private:
    int price;
public:
    Movie(int price_) : price(price_) {}
    int getPrice() const { return price; }

    int accept(Visitor& visitor_) override
    {
        return visitor_.visit(*this);
    }
};
```
3. 마지막으로 visitor인터페이스를 상속받은 visitor클래스를 구현한다.
```cpp
class PriceVisitor : public Visitor
{
public:
    int visit(Book& book) override
    {
        return book.getPrice();
    }

    int visit(Music& music) override
    {
        return music.getPrice();
    }

    int visit(Movie& movie) override
    {
        return movie.getPrice();
    }
};
```
4. 별도로 구현된 기능을 사용한다.
```cpp
int main() {
    std::shared_ptr<Goods> g = std::make_shared<Book>(150);

    std::shared_ptr<Visitor> pv = std::make_shared<PriceVisitor>();

    std::cout << g->accept(*pv); // 150 출력!

    return 0;
}
```

## 왜 사용할까?
객체의 구조를 변경시키지 않고 새로운 동작을 추가할 수 있다. <br/>
특정한 동작만 추가하려는데 기존의 클래스를 수정하지 않기 때문에 기존에 정의된 동작들과 관계없이 새로운 동작을 추가할 수 있다. <br/>
또한 잘 활용하면 ```dynamic_cast```의 사용을 줄일 수 있다.

### Dynamic_cast와 visitor패턴
```dynamic_cast```의 오버헤드는 어디에서 올까? <br/>
```vtable```에 있는 정보를 탐색하기 때문이기도 하지만, 정확히는 ```vtable```의 ```RTTI```를 문자열비교하는데 걸리는 시간 때문이다. <br/>
```dynamic_cast```를 통해 다형성객체를 판단하여 동작을 수행해야하는 경우, <br/>
```visitor```패턴을 사용하여 동작을 구현해준다면 ```dynamic_cast```의 사용을 줄일 수 있다. <br/>
```dynamic_cast```의 ```RTTI```조회는 런타임에 수행되지만, 함수 오버로딩의 타입판단은 컴파일타임에 진행되므로 런타임에 발생할 오버헤드를 줄일 수 있는 것이다.
