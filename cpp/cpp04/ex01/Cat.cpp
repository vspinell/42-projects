/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:27:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/20 19:25:56 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal() {
	
	std::cout << "Cat constructor called" << std::endl;
	this->type = "Cat";
	this->_brain = new Brain();
}

Cat::~Cat() {
	std::cout << "Cat destructor called" << std::endl;
	delete _brain;
}

void		Cat::makeSound() const {
	std::cout << "Miao" << std::endl;
}

Cat::Cat(const Cat &p1) {
	this->_brain = new Brain();
	this->operator=(p1);
}

Cat& Cat::operator = (const Cat &p1) {
	
	this->type = p1.type;
	*this->_brain = *p1._brain;
	return *this;
}

void Cat::printaddress() const {
	
	std::cout << this->_brain << std::endl;
}