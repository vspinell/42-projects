/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:00:20 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/18 17:32:47 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() {
	std::cout << "Animal constructor called" << std::endl;
}

Animal::~Animal() {
	
	std::cout << "Animal destructor called" << std::endl;
}

std::string Animal::getType() const {
	return type;
}