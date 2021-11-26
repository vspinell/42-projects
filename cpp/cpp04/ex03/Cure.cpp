/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:22:43 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/26 13:08:38 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"


Cure::Cure() : AMateria("cure") {

	std::cout << "Cure's DEFAULT CONSTRUCTOR called" << std::endl;
}

Cure::~Cure() {
	
	std::cout << "Cure's DEFAULT DESTRUCTOR called" << std::endl;
}

Cure::Cure(const Cure &src) {
	
	this->operator=(src);
}

Cure& Cure::operator = (const Cure &src) {
	
	if (this != &src)
		this->_type = src._type;
	return *this;
}

AMateria* Cure::clone() const {
	
	return (new Cure(*this));
	// return tmp;
}

void Cure::use ( ICharacter& target ) {
	
	std::cout << "* heals " << target.getName() << "’s wounds *\n";
}