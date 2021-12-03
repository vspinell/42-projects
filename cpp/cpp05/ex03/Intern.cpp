/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:27:03 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/03 19:24:27 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(Intern const &src) {
	(void)src;
}

Intern::~Intern() {}

AForm*	Intern::makeForm(std::string const formType, std::string const formTarget) {

	size_t pos;
	AForm* ret = NULL;

	std::string forms[3] = {"robotomy", "presidential", "shruberry"};
	for(int i = 0; i < 3; i++)
	{
		pos = formType.find(forms[i]);
		if (pos != std::string::npos)
		{
			switch (i)
			{
				case 0:
					ret = new RobotomyRequestForm(formTarget);
					std::cout << "Intern has created the form: " << ret->getName() << std::endl;
					break;
				case 1:
					ret = new PresidentialPardonForm(formTarget);
					std::cout << "Intern has created the form: " << ret->getName() << std::endl;
					break;
				case 2:
					ret = new ShrubberyCreationForm(formTarget);
					std::cout << "Intern has created the form: " << ret->getName() << std::endl;
					break;
				default:
					break;
			}
			return (ret);
		}
	}
	throw Intern::Unknownform();
}

const char* Intern::Unknownform::what() const throw() {
	return ("Unknown Form request");
}