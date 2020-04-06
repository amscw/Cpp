//============================================================================
// Name        : templates.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

/**
 * Вспомогательные типы для организации списков
 */
template <class T, class U>
struct Typelist
{
	typedef T Head;
	typedef U Tail;
};

class NullType{};

/**
 * Тип порт
 */
enum class port_t : char {A = 'A', B = 'B', C = 'C', D = 'D', E = 'E', F = 'F'};

template <port_t port>
struct Port
{
	enum {PORT = static_cast<int>(port)};
};

/**
 * Тип пин
 */
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

/**
 * Обертка для пина,содержащая номер пина в списке
 */

template <int pos, class pin>
struct PW
{
	typedef pin Pin;
	enum {POSITION = pos};
};

/**
 * Типы для генерации списка пинов
 */
template<int Pos, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType>
struct MakePinList
{
private:
	enum{PositionInList = Pos};
	typedef typename MakePinList<Pos + 1, T2, T3, T4>::Result TailResult;
public:
	typedef Typelist<PW<Pos, T1>, TailResult> Result;
};

template<int Pos>
struct MakePinList<Pos/*, NullType, NullType, NullType, NullType*/>
{
	typedef NullType Result;
	enum{PositionInList = Pos};
};

/**
 * Типы для генерации списка портов
 */
template <class TList> struct GetPorts;

template <class Head, class Tail>
struct GetPorts< Typelist<Head, Tail> >
{
private:
	// запоминаем порт, к которому относится пин из PW
	typedef typename Head::Pin::Port Port;	// Head = PW
	// TailResult есть Result следующего инстанса
	typedef typename GetPorts<Tail>::Result TailResult;
public:
	// Result текущего инстанса есть Typelist "откушенной" головы и
	// остальной части списка
	typedef Typelist<Port, TailResult> Result;
};

template <> struct GetPorts<NullType>
{
	typedef NullType Result;
};

/**
 * Создаем список пинов и список портов
 */
typedef MakePinList<0, PA0, PB1, PC1, PC2>::Result PinList;
typedef GetPorts<PinList> PortList;


int main() {



	return 0;
}
