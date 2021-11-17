/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:02:03 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/17 17:45:55 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() {
	
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name) {
	
	this->_name = name;
	this->Hitpoints = FragTrap::Hitpoints;
	this->Energy_points = ScavTrap::Energy_points; 
	this->Attack_damage = FragTrap::Attack_damage;
	std::cout << "DiamondTrap CONSTRUCTOR called" << std::endl;
}

DiamondTrap& DiamondTrap::operator = (const DiamondTrap &p1) {
	this->Name = p1.Name;
	this->Hitpoints = p1.Hitpoints;
	this->Energy_points = p1.Energy_points;
	this->Attack_damage	= p1.Attack_damage;
	return *this;
}

DiamondTrap::DiamondTrap(const DiamondTrap &p1) : ClapTrap(p1), ScavTrap(p1), FragTrap(p1) {
	this->operator=(p1);
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap DESTRUCTOR called" << std::endl;
}

void DiamondTrap::attack(std::string const & target) {
	this->ScavTrap::attack(target);
}

void DiamondTrap::whoAmI() {
	std::cout << "My name is: " << this->_name << std::endl;
	std::cout << "The ClapTrap's name is: " <<  ClapTrap::Name << std::endl;
}