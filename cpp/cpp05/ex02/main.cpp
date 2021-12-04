/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:27:46 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/04 12:22:11 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"


int main()
{
	try
	{
		AForm *b = new ShrubberyCreationForm("Gulielmo");
		std::cout << "Name: " << b->getName() << std::endl;
		std::cout << "Sign grade: " << b->getSignGrade() << std::endl;
		std::cout << "Execute grade: " << b->getExecGrade() << std::endl;
		std::cout << "--------------------------------\n";
		b->actions();
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		AForm *b = new RobotomyRequestForm("Gulielmo");
		std::cout << "Name: " << b->getName() << std::endl;
		std::cout << "Sign grade: " << b->getSignGrade() << std::endl;
		std::cout << "Execute grade: " << b->getExecGrade() << std::endl;
		b->actions();
		std::cout << "--------------------------------\n";
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		AForm *b = new PresidentialPardonForm("Gulielmo");
		std::cout << "Name: " << b->getName() << std::endl;
		std::cout << "Sign grade: " << b->getSignGrade() << std::endl;
		std::cout << "Execute grade: " << b->getExecGrade() << std::endl;
		b->actions();
		std::cout << "--------------------------------\n";
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	
	
}