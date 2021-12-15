/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:42:01 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/13 15:22:35 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

int main()
{
	{
		int a,b;
		a = 1;
		b = 2;
		std::cout << "Int TRIAL\nA: " << a << "   |   B: " << b << std::endl;
		std::cout << "Min: " << ::min(a, b) << std::endl;
		std::cout << "Max: " << ::max(a, b) << std::endl;
		::swap(a,b);
		std::cout << "After swap...\nA: " << a << "   |   B: " << b << std::endl;
	}
	{
		char a,b;
		a = 'b';
		b = 'x';
		std::cout << "\nChar TRIAL\nA: " << a << "   |   B: " << b << std::endl;
		std::cout << "Min: " << ::min(a, b) << std::endl;
		std::cout << "Max: " << ::max(a, b) << std::endl;
		::swap(a,b);
		std::cout << "After swap...\nA: " << a << "   |   B: " << b << std::endl;
	}
	{
		float a,b;
		a = -1.79f;
		b = -1.78f;
		std::cout << "\nFloat TRIAL\nA: " << a << "   |   B: " << b << std::endl;
		std::cout << "Min: " << ::min(a, b) << std::endl;
		std::cout << "Max: " << ::max(a, b) << std::endl;
		::swap(a,b);
		std::cout << "After swap...\nA: " << a << "   |   B: " << b << std::endl;
	}
	{
		std::string a, b;
		a = "pippo1";
		b = "pipppo2";
		std::cout << "\nString TRIAL\nA: " << a << "   |   B: " << b << std::endl;
		std::cout << "Min: " << ::min(a, b) << std::endl;
		std::cout << "Max: " << ::max(a, b) << std::endl;
		::swap(a,b);
		std::cout << "After swap...\nA: " << a << "   |   B: " << b << std::endl;
	}
}