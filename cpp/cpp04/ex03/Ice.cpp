/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:32:49 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 15:03:05 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {

	std::cout << "Ice's DEFAULT CONSTRUCTOR called" << std::endl;
}

Ice::~Ice() {
	
	std::cout << "Ice's DEFAULT DESTRUCTOR called" << std::endl;
}

AMateria* clone() const {
	
	AMateria *tmp = new Ice(*this);
	return tmp;
}

void Ice::use(ICharacter& target) {
	
	std::cout << "* shoots an ice bolt at " << target.getName() << " *\n";
}