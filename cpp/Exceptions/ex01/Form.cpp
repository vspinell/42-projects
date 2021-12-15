/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:46:02 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/01 14:25:31 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form( void ) : _name("pippo Baudo"), _sign_grade(42), _exec_grade(42) {}

Form::Form(std::string const name, unsigned int const sign_grade, unsigned int const exec_grade) : 
			_name(name), _status(0) , _sign_grade(sign_grade), _exec_grade(exec_grade)
{
	if ((int)sign_grade < 1 || (int)exec_grade < 1)
		throw Form::GradeTooHighException();
	else if (sign_grade > 150 || exec_grade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form &src) : 
	_name(src._name), _sign_grade(src._sign_grade), _exec_grade(src._exec_grade)
{
	this->operator=(src);
}

Form::~Form( void ) {
	
}


/*
**-----------------Costructors/Destructor-------------------**
*/

std::ostream &operator <<(std::ostream &output, const Form &obj) {

	std::string stat = obj.getStatus() == 1 ? "Signed" : "NOT Signed";
	output << "------------------------------------\n" << obj.getName() \
	<< " - Form\nGrade required to SIGN: [" << obj.getSignGrade() \
	<< "]\nGrade required to EXECUTE: [" << obj.getExecGrade() << "]\nStatus: "\
	<< stat << "\n------------------------------------\n";
	return output;

}

Form& Form::operator = (const Form &src) {
	
	if (this != &src)
	{
		this->_status = src._status;
	}
	return *this;
}

/*
**-----------------Overload operators-------------------**
*/


void				Form::trytoSign(Bureaucrat &b) {
	
	if (this->getStatus())
		throw Form::Alreadysigned();
	else if (b.getGrade() <= this->_sign_grade)
		this->_status = true;
	else
		throw Form::GradeTooLowException();
}

void			Form::beSigned(Bureaucrat &b) {

	try
	{
		this->trytoSign(b);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

unsigned int		Form::getSignGrade( void ) const {
	return this->_sign_grade;
}
unsigned int		Form::getExecGrade( void ) const {
	return this->_exec_grade;
}
std::string const	Form::getName( void ) const {
	return this->_name;
}
bool				Form::getStatus( void ) const {
	return this->_status;
}


/*
**-----------------Public Functions-------------------**
*/

const char* Form::GradeTooHighException::what() const throw() {
	
	return ("Grade Too High");
}

const char* Form::GradeTooLowException::what() const throw() {
	
	return ("Grade Too Low");
}
const char* Form::Alreadysigned::what() const throw() {
	
	return ("Form already signed");
}


/*
**-----------------Exception handling-------------------**
*/