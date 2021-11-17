/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:41:43 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/17 17:17:00 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {
	
}

ClapTrap::ClapTrap(std::string name) {
	
	this->Name = name;
	this->Hitpoints = 10;
	this->Energy_points = 10;
	this->Attack_damage	= 0;
	std::cout << "ClapTrap " << this->Name << " Constructor called" << std::endl;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap Destructor called" << std::endl;

}

ClapTrap::ClapTrap(const ClapTrap& p1) {
	this->operator=(p1);
}

ClapTrap& ClapTrap::operator= (const ClapTrap &p1) {
	
	this->Name = p1.Name;
	this->Hitpoints = p1.Hitpoints;
	this->Energy_points = p1.Energy_points;
	this->Attack_damage	= p1.Attack_damage;
	return *this;
}

void ClapTrap::attack(std::string const & target) {

	std::cout << this->Name << " attacks " << target << " , causing " << this->Attack_damage << " points of damage!" << std::endl;
}
void ClapTrap::takeDamage(unsigned int amount) {

	std::cout << this->Name << " take damage of " << amount << ", " << this->Hitpoints - amount << " remaining hitpoints!" << std::endl;
}
void ClapTrap:: beRepaired(unsigned int amount) {

	std::cout << this->Name << " has been repaired for an amount of " << amount << ", " << this->Energy_points + amount << " energy points!" << std::endl;
}