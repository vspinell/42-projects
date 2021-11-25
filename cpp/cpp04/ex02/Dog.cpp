/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:02:05 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/20 19:25:38 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal() {
	
	std::cout << "Dog constructor called" << std::endl;
	this->type = "Dog";
	this->_brain = new Brain();
	// address = this;
}

void Dog::printaddress() const {
	
	std::cout << this->_brain << std::endl;
}

Dog::~Dog() {
	std::cout << "Dog destructor called" << std::endl;
	delete _brain;
}

Dog::Dog(const Dog &p1) {

	this->_brain = new Brain();
	this->operator=(p1);
}


Dog& Dog::operator = (const Dog &p1) {
	
	this->type = p1.type;
	*this->_brain = *p1._brain;
	return *this;
}

void		Dog::makeSound() const {
	std::cout << "Bau" << std::endl;
}