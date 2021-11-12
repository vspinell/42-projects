/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:54:59 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/12 13:25:37 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name) {

}

Zombie::~Zombie() {

	std::cout << "Destroier has killed " << this->_name << std::endl;
}

void	Zombie::announce( void ) {

	std::cout << "<" << this->_name << "> BraiiiiiiinnnzzzZ..." << std::endl;
}