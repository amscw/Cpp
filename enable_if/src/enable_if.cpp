//============================================================================
// Name        : enable_if.cpp
// Author      : moskvin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

/*
 * Шаблон класса (не инстанцируется)
 */
template <bool predicate_value, class result_type = void>
struct enable_if;

/*
 * Специализация шаблона есть только для значения параметра
 * predicate_value = true
 */
template <class result_type>
struct enable_if<true, result_type>
{
	typedef result_type type;
};

/*
 * Таким образом, код не скомпилируется, в случае ложного значения
 * предиката, т.к. не существует общего шаблона и не существует
 * требуемой специализации для false
 *
 * В качестве аргументов std::enable_if могут быть использованы самые
 * разнообразные структуры-предикаты из того же <type_traits>:
 * std::is_signed::value истино, если T является знаковым
 * std::is_floating_point::value истино для вещественнных типов
 * std::is_same<T1, T2>::value истино, если T1 и T2 совпадают
 *
 * поле type структуры enable_if можно использовать далее в коде
 */

/*
 * Предикат - это обычная частиная специализация шаблонной структуры.
 * Например, для std::is_same
 */
template <class T1, class T2>
struct is_same
{
	static const bool value = false;
};

template <class T>
struct is_same<T, T>
{
	static const bool value = true;
};

/*
 * Компилятор будет пытаться использовать в первую очередь
 * именно частичную специализацию, поэтому он выберет второй шаблон.
 * Это не скомпилируется для разных типов, значит он выберет общую,
 * для которой предикат имеет значение false
 *
 * Компилятор всегда пытается отыскать строго подходящую специализацию
 * по типам аргументов и, лишь не найдя нужную,
 * идет в общую реализацию шаблона.
 */
int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	// ок
	enable_if<is_same<int, int>::value, double>::type myvar;
	// не скомпилируется
	// enable_if<is_same<int, double>::value, double>::type myvar;
	return 0;
}
