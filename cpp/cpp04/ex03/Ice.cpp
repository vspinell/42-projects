/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:32:49 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/26 11:55:20 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {

	std::cout << "Ice's DEFAULT CONSTRUCTOR called" << std::endl;
}

Ice::~Ice() {
	
	std::cout << "Ice's DEFAULT DESTRUCTOR called" << std::endl;
}

Ice::Ice(const Ice &src) {
	
	this->operator=(src);
}

Ice& Ice::operator = (const Ice &src) {
	
	if (this != &src)
		this->_type = src._type;
	return *this;
}

AMateria* Ice::clone() const {
	
	return  (new Ice(*this));
}

void Ice::use(ICharacter& target) {
	
	std::cout << "* shoots an ice bolt at " << target.getName() << " *\n";
}