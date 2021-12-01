/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:27:46 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/30 19:42:19 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
	try 
	{
		Bureaucrat b1("Targeted", 145);
		while (1)
		{
			b1.decrementGrade();
			std::cout << b1 << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "----------------------------------------\n";
	}
	try 
	{
		Bureaucrat b1("Excellent Employee", 5);
		while (1)
		{
			b1.incrementGrade();
			std::cout << b1 << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "----------------------------------------\n";
	}
	try 
	{
		Bureaucrat b1("Camillo", 1);
		std::cout << b1 << std::endl;
		Bureaucrat b2("Filippo", -1);
		std::cout << b2 << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "----------------------------------------\n";
	}
}