/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:00:20 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 11:49:10 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

Animal::Animal() :type("Lion") {
	std::cout << "Animal constructor called" << std::endl;

}

Animal::~Animal() {
	
	std::cout << "Animal destructor called" << std::endl;
}

Animal::Animal(const Animal &p1) {
	this->operator=(p1);
}

Animal& Animal::operator = (const Animal &p1) {
	
	this->type = p1.type;
	return *this;
}

std::string Animal::getType( void ) const {
	return type;
}


void		Animal::makeSound() const {
	std::cout << "This is the sound of the Animal...ROARRRRR" << std::endl;
}