/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:54:39 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/26 15:37:56 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() {
	
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	std::cout << "Fragtrap CONSTRUCTOR called" << std::endl;
	this->Hitpoints = 100;
	this->Energy_points = 100;
	this->Attack_damage	= 30;
}

FragTrap::~FragTrap() {
	std::cout << "Fragtrap DESTRUCTOR called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &p1) : ClapTrap(p1) {
	this->operator=(p1);
}

FragTrap& FragTrap::operator = (const FragTrap &p1) {

	this->Name = p1.Name;
	this->Hitpoints = p1.Hitpoints;
	this->Energy_points = p1.Energy_points;
	this->Attack_damage	= p1.Attack_damage;
	return *this;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "Give me a high five!" << std::endl;
}

void FragTrap::attack(std::string const & target) {
	std::cout << "Frag " << this->Name << " attacks " << target << " , causing " \
	<< this->Attack_damage << " points of damage!" << std::endl;
}