/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:27:46 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/04 15:04:11 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "Intern.hpp"


int main(int ac, char **av)
{
	if (ac == 2)
	{
		try
		{
			Intern someRandomIntern;
			AForm* rrf;
			rrf = someRandomIntern.makeForm(av[1], "Bender");
			std::cout << "The name of the form is: " << rrf->getName() << std::endl;
			rrf->actions();
			delete rrf;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}