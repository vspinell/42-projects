/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:04:40 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/19 13:04:41 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal() {
	
	std::cout << "WrongCat constructor called" << std::endl;
	this->type = "WrongCat";
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat destructor called" << std::endl;
}

void		WrongCat::makeSound() const {
	std::cout << "Miu Miu" << std::endl;
}

WrongCat::WrongCat(const WrongCat &p1) {
	this->operator=(p1);
}

WrongCat& WrongCat::operator = (const WrongCat &p1) {
	
	this->type = p1.type;
	return *this;
}

