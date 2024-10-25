/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:27:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/19 12:42:27 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal() {
	
	std::cout << "Cat constructor called" << std::endl;
	this->type = "Cat";
}

Cat::~Cat() {
	std::cout << "Cat destructor called" << std::endl;
}

void		Cat::makeSound() const {
	std::cout << "Miao" << std::endl;
}

Cat::Cat(const Cat &p1) {
	this->operator=(p1);
}

Cat& Cat::operator = (const Cat &p1) {
	
	this->type = p1.type;
	return *this;
}

