/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:54:39 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/17 13:55:04 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"


FragTrap::FragTrap(std::string name) : ClapTrap("name") {
	std::cout << "Fragtrap CONSTRUCTOR called" << std::endl;
	this->Name = name;
	this->Hitpoints = 100;
	this->Energy_points = 50;
	this->Attack_damage	= 20;
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

void FragTrap::guardGate() {
	std::cout << this->Name << " has entered in Gate keeper mode" << std::endl;
}