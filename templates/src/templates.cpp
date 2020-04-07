//============================================================================
// Name        : templates.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "utils.hpp"

template <class T, class U>
struct Typelist {
	typedef T Head;
	typedef U Tail;
};

class NullType{};

/**
 * Тип порта
 */
enum class port_t : char {A = 'A', B = 'B', C = 'C', D = 'D', E = 'E', F = 'F'};
template <port_t port> struct Port { static const port_t Value{port}; };



template <port_t port, int pin> class pin_c
{
public:
	enum { NUMBER = pin };
	typedef Port<port> Port;
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

/**
 * Обёртка для задания номера позиции в списке
 */
template <class pin_c, int Pos>
struct PW
{
	typedef pin_c pin;
	enum {Position = Pos};
};

/**
 * Шаблон, генерирующий список типов на основе Typelist
 */
template<int Pos, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType>
struct MakePinList
{
private:
	enum{PositionInList = Pos};
	typedef typename MakePinList<Pos + 1, T2, T3, T4>::Result TailResult;

public:
	typedef Typelist<PW<T1, PositionInList>, TailResult> Result;
};

template<int Pos>
struct MakePinList<Pos, NullType, NullType, NullType, NullType>
{
	typedef NullType Result;
	enum{PositionInList = Pos};
};

/**
 * Шаблон обработки списка типов:
 * формирует новый список Typelist на основе списка Typelist из аргумента
 */

template <class TList> struct GetPorts;

template <class Head, class Tail>
struct GetPorts< Typelist<Head, Tail> >
{
private:
	// запоминаем порт
	typedef typename Head::pin::Port Port;	// Head = PW
	typedef typename GetPorts<Tail>::Result TailResult;
public:
	typedef Typelist<Port, TailResult> Result;
};

template <> struct GetPorts<NullType>
{
	typedef NullType Result;
};

typedef MakePinList<0, PA0, PB1, PC1, PC2>::Result PinList;
typedef GetPorts<PinList>::Result PortList;

// test utils
typedef TypeList<int, unsigned int, signed int> Ints;
typedef TypeList<float, double, long double> Doubles;

int main() {
	std::cout << "Ints is empty: " << std::boolalpha << IsEmpty<Ints>::value << std::endl;
	std::cout << "EmptyTypeList is empty: " << std::boolalpha << IsEmpty<EmptyTypeList>::value << std::endl;
	std::cout << "Doubles contains int: " << std::boolalpha << Contains<int, Doubles>::value << std::endl;
	std::cout << "Doubles contains float: " << std::boolalpha << Contains<float, Doubles>::value << std::endl;
	std::cout << "Length of Ints = " << Length<Ints>::value << std::endl;
	return 0;
}
