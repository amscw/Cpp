//============================================================================
// Name        : simple-tuple.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

/**
 * В качестве элементов кортежа будем использовать класс pin_c
 */
enum class port_t : char {A = 'A', B = 'B', C = 'C', D = 'D', E = 'E', F = 'F'};

template <port_t port, int pin> class pin_c
{
public:
	enum { NUMBER = pin };
	static const port_t PORT{port};

	static void Print() { std::cout << "P" << static_cast<char>(port) << pin ; }
};

using PA0 = pin_c<port_t::A, 0>;
using PA1 = pin_c<port_t::A, 1>;
using PB0 = pin_c<port_t::B, 0>;
using PB1 = pin_c<port_t::B, 1>;
using PC0 = pin_c<port_t::C, 0>;
using PC1 = pin_c<port_t::C, 1>;
using PC2 = pin_c<port_t::C, 2>;
using PC3 = pin_c<port_t::C, 3>;

/*
 * Базовый шаблон никогда не инстанцируется,
 * компилятор выберет только частные
 */
template <typename ... Args> struct tuple;

template <typename Head, typename ... Tail>
struct tuple<Head, Tail...> : tuple<Tail...>
{
	// тип базового класса сохраняем в текущем
	typedef tuple<Tail...> base_type;
	// тип текущего аргумента шаблона также сохраняем
	typedef Head value_type;

	tuple() : tuple<Tail...>()
	{

	}
};

/*
 * Специализация шаблона, соответствующая пустому пакету параметров
 * (последний генерируемый класс в цепочке наследования, дно рекурсии)
 */
template<> struct tuple<>{};

using AddrPins = tuple<PA0, PB1, PC2, PC3>;

/**
 * Аксессор типа кортежа, задаваемого индексом I.
 * Для всякого I компилятор будет генерировать I-1 шаблон,
 * пока не дойдет до шаблона с I=0
 */
template<int I, typename Head, typename... Args> struct getter
{
	typedef typename getter<I-1, Args...>::pin_type pin_type;
};

/*
 * Шаблон с I=0
 */
template<typename Head, typename... Args> struct getter<0, Head, Args...>
{
	typedef typename tuple<Head, Args...>::value_type pin_type;
};

struct ForeachCallback
{
	// параметр необходим для вывода типов шаблона
	template<int I, typename Head, typename... Args>
	void operator()(tuple<Head, Args...>)
    {
		typedef typename getter<I, Head, Args...>::pin_type pin;

    	// Выполняем любую работу с пином
		pin::Print();
    }
};



int main() {
	// getter<2, PA0, PB1, PC2, PC3>::pin_type::Print();

	ForeachCallback f;
	f.operator()<2>(AddrPins());


	// std::cout << "sizeof t = " << sizeof test << std::endl;

	return 0;
}
