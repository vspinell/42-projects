/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:02:05 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/19 13:19:18 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal() {
	
	std::cout << "Dog constructor called" << std::endl;
	this->type = "Dog";
}

Dog::~Dog() {
	std::cout << "Dog destructor called" << std::endl;
}

Dog::Dog(const Dog &p1) {
	this->operator=(p1);
}

Dog& Dog::operator = (const Dog &p1) {
	
	this->type = p1.type;
	return *this;
}

void		Dog::makeSound() const {
	std::cout << "Bau" << std::endl;
}