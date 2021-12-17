/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:49:12 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/17 17:03:54 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

int main()
{
	try
	{
		Span myarr(5);
		Span second_arr;
		myarr.addNumber(5);
		myarr.addNumber(3);
		myarr.addNumber(17);
		myarr.addNumber(9);
		myarr.addNumber(11);

		std::cout << myarr.shortestSpan() << std::endl;
		std::cout << myarr.longestSpan() << std::endl;

		Span pippo;
		second_arr = pippo;
		std::cout << second_arr.longestSpan() << std::endl;
	}
	catch(const char * e)
	{
		std::cerr << e << '\n';
	}
	
	try
	{
		Span myarr(2);
		Span second_arr;
		myarr.addNumber(13);
		myarr.addNumber(36);
		myarr.addNumber(21);

	}
	catch(const char * e)
	{
		std::cerr << e << '\n';
	}
	try
	{
		int n;
		std::cout << "\nNote that a number higher than 10000 can take a while\nInsert the number   ";
		std::cin >> n;
		Span myarr(n);
		srand(time(0));
		for (int i = 0; i < n; i++)
			myarr.addNumber(rand() % rand());

		std::cout << myarr.shortestSpan() << std::endl;
		std::cout << myarr.longestSpan() << std::endl;
	}
	catch(const char * e)
	{
		std::cerr << e << '\n';
	}
	
}