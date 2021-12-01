/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:46:02 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/01 14:25:31 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm( void ) : _name("pippo Baudo"), _sign_grade(42), _exec_grade(42) {}

AForm::AForm(std::string const name, unsigned int const sign_grade, unsigned int const exec_grade) : 
			_name(name), _status(0) , _sign_grade(sign_grade), _exec_grade(exec_grade)
{
	if ((int)sign_grade < 1 || (int)exec_grade < 1)
		throw AForm::GradeTooHighException();
	else if (sign_grade > 150 || exec_grade > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm &src) : 
	_name(src._name), _sign_grade(src._sign_grade), _exec_grade(src._exec_grade)
{
	this->operator=(src);
}

AForm::~AForm( void ) {
	
}


/*
**-----------------Costructors/Destructor-------------------**
*/

std::ostream &operator <<(std::ostream &output, const AForm &obj) {

	std::string stat = obj.getStatus() == 1 ? "Signed" : "NOT Signed";
	output << "------------------------------------\n" << obj.getName() \
	<< " - AForm\nGrade required to SIGN: [" << obj.getSignGrade() \
	<< "]\nGrade required to EXECUTE: [" << obj.getExecGrade() << "]\nStatus: "\
	<< stat << "\n------------------------------------\n";
	return output;

}

AForm& AForm::operator = (const AForm &src) {
	
	if (this != &src)
	{
		this->_status = src._status;
	}
	return *this;
}

/*
**-----------------Overload operators-------------------**
*/


void				AForm::trytoSign(Bureaucrat &b) {
	
	if (this->getStatus())
		throw AForm::Alreadysigned();
	else if (b.getGrade() <= this->_sign_grade)
		this->_status = true;
	else
		throw AForm::GradeTooLowException();
}

void			AForm::beSigned(Bureaucrat &b) {

	try
	{
		this->trytoSign(b);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

unsigned int		AForm::getSignGrade( void ) const {
	return this->_sign_grade;
}
unsigned int		AForm::getExecGrade( void ) const {
	return this->_exec_grade;
}
std::string const	AForm::getName( void ) const {
	return this->_name;
}
bool				AForm::getStatus( void ) const {
	return this->_status;
}


/*
**-----------------Public Functions-------------------**
*/

const char* AForm::GradeTooHighException::what() const throw() {
	
	return ("Grade Too High");
}

const char* AForm::GradeTooLowException::what() const throw() {
	
	return ("Grade Too Low");
}
const char* AForm::Alreadysigned::what() const throw() {
	
	return ("AForm already signed");
}


/*
**-----------------Exception handling-------------------**
*/