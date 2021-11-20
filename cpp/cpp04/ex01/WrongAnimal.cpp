/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:01:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/19 13:03:54 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() :type("FakeLion") {
	std::cout << "WrongAnimal constructor called" << std::endl;

}

WrongAnimal::~WrongAnimal() {
	
	std::cout << "WrongAnimal destructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &p1) {
	this->operator=(p1);
}

WrongAnimal& WrongAnimal::operator = (const WrongAnimal &p1) {
	
	this->type = p1.type;
	return *this;
}

std::string WrongAnimal::getType() const {
	return type;
}

void		WrongAnimal::makeSound() const {
	std::cout << "This is the sound of the WrongAnimal...grrr...sorry I'm trying my best" << std::endl;
}
