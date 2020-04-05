//============================================================================
// Name        : templates.cpp
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

class NullType{};

template<int Pos, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType>
struct MakePinList
{
	enum{PositionInList = Pos};
	typedef typename MakePinList<Pos + 1, T2, T3, T4>::Result TailResult;
};

template<int Pos>
struct MakePinList<Pos/*, NullType, NullType, NullType, NullType*/>
{
	typedef NullType Result;
	enum{PositionInList = Pos};
};

typedef MakePinList<0, PA0, PB1, PC1, PC2>::TailResult PinList_c;



int main() {



	return 0;
}
