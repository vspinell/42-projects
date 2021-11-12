/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:54:59 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/12 18:12:08 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int Zombie::i = 1;

Zombie::Zombie() {
	
}

Zombie::~Zombie() {

	std::cout << "Destroier has killed " << this->i << "˚" << this->_name << std::endl;
	Zombie::i++;
}

void	Zombie::announce( void ) {

	std::cout << "<" << this->_name << "> BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::set_name(std::string name) {
	this->_name = name;
}