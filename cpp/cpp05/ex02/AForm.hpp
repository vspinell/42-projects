/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:46:30 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/01 15:02:47 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_H
#define AFORM_H

#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
	public:
		AForm();
		AForm(std::string const name, unsigned int const sign_grade, unsigned int const exec_grade);
		AForm(const AForm &src);
		virtual ~AForm();

		AForm& operator = (const AForm &src);

		class GradeTooHighException : public std::exception {
			const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			const char* what() const throw();
		};
		class Alreadysigned : public std::exception {
			const char* what() const throw();
		};
		unsigned int		getSignGrade( void ) const;
		unsigned int		getExecGrade( void ) const;
		std::string const	getName( void ) const;
		bool				getStatus( void ) const;
		void				trytoSign(Bureaucrat &b);

		void				beSigned(Bureaucrat &b);
		void				execute(Bureaucrat const & executor) const;
		virtual void		actions( void ) = 0;
		
	private :
		std::string const	_name;
		bool				_status;
		unsigned int const	_sign_grade;
		unsigned int const	_exec_grade;
};

std::ostream &operator <<(std::ostream &output, const AForm &obj);


#endif
