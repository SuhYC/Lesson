#include <iostream>
#include <ctime>
#include <exception>
#include <unordered_map>

const int TASK = 10000;

enum class Ret
{
	SUC,
	FAIL
};

typedef void(*ACT)();
std::unordered_map<Ret, ACT> map = std::unordered_map<Ret, ACT>();
std::vector<ACT> vec = std::vector<ACT>();

class SomeException : public std::exception
{
public:
	SomeException(const char* message) : msg(message)
	{

	}

	const char* what() const noexcept override
	{
		return msg;
	}

private:
	const char* msg;
};


void Except()
{
	throw SomeException("Fail");

	return;
}

Ret Enum()
{
	return Ret::FAIL;
}

void Suc()
{
	std::cout << "SUC" << "\n";
	return;
}

void Fail()
{
	std::cout << "Fail" << "\n";
}

void Test1()
{
	int cnt = TASK;

	while (cnt--)
	{
		try
		{
			Except();
		}
		catch (SomeException& e)
		{
			std::cout << e.what() << "\n";
		}
	}

	return;
}

void Test2()
{
	int cnt = TASK;

	while (cnt--)
	{
		Ret ret = Enum();

		auto itr = map.find(ret);
		if (itr == map.end())
		{
			std::cerr << "¿¨\n";
			continue;
		}

		(*(itr->second))();
	}
}

void Test3()
{
	int cnt = TASK;

	while (cnt--)
	{
		Ret ret = Enum();

		switch (ret)
		{
		case Ret::SUC:
			Suc();
			break;
		case Ret::FAIL:
			Fail();
			break;
		default:
			std::cout << "NotDefined\n";
		}
	}
}

void Test4()
{
	int cnt = TASK;
	
	while (cnt--)
	{
		Ret ret = Enum();
		
		size_t idx = static_cast<size_t>(ret);

		if (idx >= vec.size())
		{
			continue;
		}
		vec[idx]();
	}
}

int main()
{
	map.emplace(Ret::SUC, &Suc);
	map.emplace(Ret::FAIL, &Fail);

	vec.push_back(&Suc);
	vec.push_back(&Fail);

	clock_t st = clock();

	Test4();

	clock_t end = clock();

	std::cout << "\n\n" << end - st;

	return 0;
}