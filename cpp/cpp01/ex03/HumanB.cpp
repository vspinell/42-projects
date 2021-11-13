/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:29:41 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 11:46:41 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _Name(name) {
	
}

HumanB::~HumanB() {
	
}

void	HumanB::attack()  {
	std::cout << this->_Name << "attacks with his " << this->_Weapon->get_str() << std::endl;
}

void	HumanB::set_weapon(Weapon &haxPTR) {
	this->_Weapon = &haxPTR;
}