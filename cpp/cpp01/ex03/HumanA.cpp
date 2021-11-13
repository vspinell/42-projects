/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:29:28 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 10:55:25 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& club) : _Name(name), _Weapon(club){

}

HumanA::~HumanA() {
	
}

void	HumanA::attack() {
	std::cout << this->_Name << "attacks with his " << this->_Weapon.get_str() << std::endl;
}