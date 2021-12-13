/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:14:07 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/13 13:18:44 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

class Base {
	public:
		virtual ~Base() {};
		virtual void pippo(void) = 0;
};

class A : public Base {
	public:
		A() {}
		~A() {}
		void pippo(void) {std::cout << "si son io A\n";}
};

class B : public Base {
	public:
		B() {}
		~B() {}
		void pippo(void) {std::cout << "si son io B\n";}
};

class C : public Base {
	public:
		C() {}
		~C() {}
		void pippo(void) {std::cout << "si son io C\n";}
};

Base * generate(void)
{
	srand(time(0));
	int r = rand() % 3;
	Base* ret = 0;
	switch (r)
	{
		case 0: ret = new A; break; 
		case 1: ret = new B; break;
		case 2: ret = new C; break;
	}
	return (ret);
}

void identify(Base* p)
{

	A* a = dynamic_cast<A*>(p);
	if (a != 0)
		std::cout << "A\n";
	B* b = dynamic_cast<B*>(p);
	if (b != 0)
		std::cout << "B\n";
	C* c = dynamic_cast<C*>(p);
	if (c != 0)
		std::cout << "C\n";
}

void identify(Base& p)
{
	try
	{
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A\n";
	}
	catch(const std::exception& e)
	{

	}
	try
	{
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "B\n";
	}
	catch(const std::exception& e)
	{
		// std::cerr << e.what() << '\n';
	}
	try
	{
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "C\n";
	}
	catch(const std::exception& e)
	{
		// std::cerr << e.what() << '\n';
	}
}

int main()
{
	Base* point_base;
	point_base = generate();
	std::cout << "With pointer: ";
	identify(point_base);
	std::cout << "With reference: ";
	identify(*point_base);




}
