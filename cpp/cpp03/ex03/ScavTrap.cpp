/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:47:56 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/17 17:26:59 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap () {
	
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	this->Hitpoints = 100;
	this->Energy_points = 50;
	this->Attack_damage	= 20;
	std::cout << "ScavTrap " << this->Name << " Constructor called" << std::endl;
}

ScavTrap::~ScavTrap() {
	std::cout << "Scavtrap DESTRUCTOR called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &p1) : ClapTrap(p1) {
	this->operator=(p1);
}

ScavTrap& ScavTrap::operator = (const ScavTrap &p1) {

	this->Name = p1.Name;
	this->Hitpoints = p1.Hitpoints;
	this->Energy_points = p1.Energy_points;
	this->Attack_damage	= p1.Attack_damage;
	return *this;
}

void ScavTrap::guardGate() {
	std::cout << this->Name << " has entered in Gate keeper mode" << std::endl;
}