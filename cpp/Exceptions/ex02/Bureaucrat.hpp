/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:09:32 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/01 16:43:07 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_H
#define BUREAUCRAT_H

#include <iostream>
#include <string>
#include <exception>
# include "AForm.hpp"

class AForm;

class Bureaucrat
{
	public:
		Bureaucrat();
		Bureaucrat(std::string const &name, unsigned int const &grade);
		Bureaucrat(const Bureaucrat &src);
		~Bureaucrat();

		Bureaucrat& operator = (const Bureaucrat &src);

		class GradeTooHighException : public std::exception {
			const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			const char* what() const throw();
		};

		std::string const	getName() const;
		unsigned int		getGrade() const;
		void				incrementGrade( void );
		void				decrementGrade( void );
		
		void				signForm( AForm &form);
		void				executeForm(AForm const & form) const;

	private:
		std::string const	_name;
		unsigned int		_grade;
};

std::ostream &operator <<(std::ostream &output, const Bureaucrat &obj);

#endif