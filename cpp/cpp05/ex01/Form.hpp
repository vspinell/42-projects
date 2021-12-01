/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:46:30 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/01 12:24:55 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_H
#define FORM_H

#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	public:
		Form();
		Form(std::string const name, unsigned int const sign_grade, unsigned int const exec_grade);
		Form(const Form &src);
		~Form();

		Form& operator = (const Form &src);

		class GradeTooHighException : public std::exception {
			const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			const char* what() const throw();
		};
		void				beSigned(Bureaucrat &b);
		unsigned int		getSignGrade( void ) const;
		unsigned int		getExecGrade( void ) const;
		std::string const	getName( void ) const;
		bool				getStatus( void ) const;
		void				trytoSign(Bureaucrat &b);
		
	private :
		std::string const	_name;
		bool				_status;
		unsigned int const	_sign_grade;
		unsigned int const	_exec_grade;
};

std::ostream &operator <<(std::ostream &output, const Form &obj);


#endif
