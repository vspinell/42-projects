/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:27:11 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/30 19:34:02 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat( void ) {}

Bureaucrat::Bureaucrat(std::string const &name, unsigned int const &grade) : _name(name) {
	
	if ((int)grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	else
		this->_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &src){
	
	this->operator=(src);
}

Bureaucrat::~Bureaucrat( void ) {
	
}


/*
**-----------------Costructors/Destructor-------------------**
*/

std::ostream &operator <<(std::ostream &output, const Bureaucrat &obj) {

	output << obj.getName() << ", bureaucrat grade " << obj.getGrade();
	return output;

}

Bureaucrat& Bureaucrat::operator = (const Bureaucrat &src) {
	
	if (this != &src)
	{
		this->_grade = src._grade;
	}
	return *this;
}

/*
**-----------------Overload operators-------------------**
*/

std::string const	Bureaucrat::getName() const {
	return this->_name;
}

unsigned int	Bureaucrat::getGrade() const {
	return this->_grade;
}

void	Bureaucrat::decrementGrade( void ) {

	if (this->_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	else
		++this->_grade;
}

void	Bureaucrat::incrementGrade( void ) {

	if (this->_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	else
		--this->_grade;
}

/*
**-----------------Public Functions-------------------**
*/

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	
	return ("Grade Too High");
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	
	return ("Grade Too Low");
}


/*
**-----------------Exception handling-------------------**
*/