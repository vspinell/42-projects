/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:22:43 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 16:48:40 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

#include "Cure.hpp"

Cure::Cure() : AMateria("Cure") {

	std::cout << "Cure's DEFAULT CONSTRUCTOR called" << std::endl;
}

Cure::~Cure() {
	
	std::cout << "Cure's DEFAULT DESTRUCTOR called" << std::endl;
}

AMateria* clone() const {
	
	AMateria *tmp = new Cure(*this);
	return tmp;
}

void Cure::use(ICharacter& target) {
	
	std::cout << "* heals " << target.getName() << "’s wounds *\n";
}