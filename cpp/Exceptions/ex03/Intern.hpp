/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:14:33 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/03 19:02:30 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_H
#define INTERN_H

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"

class Intern {

	public:
		Intern();
		Intern(Intern const &src);
		~Intern();

		AForm* makeForm(std::string const formType, std::string const formTarget);

		class Unknownform : public std::exception {
			const char* what() const throw();
		};

	private:
		Intern& operator = (Intern const &src);

};

#endif