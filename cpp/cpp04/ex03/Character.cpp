/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:28:38 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/26 11:48:42 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() {

}

Character::Character(std::string const & name) : _name(name) {

	std::cout << "Character's CONSTRUCTOR called" << std::endl;
	for (int i = 0; i < 4; i++)
		this->inventory[i] = NULL;
}

Character::Character(const Character &src) {
	this->operator=(src);
}

Character&	Character::operator = (const Character &src)
{
	int i = 0;
	if (this != &src)
	{
		while (this->inventory[i])
		{
			delete this->inventory[i];
			i++;
		}
		for (int i = 0; i < 4; i++)
			if (src.inventory[i])
				this->inventory[i] = src.inventory[i]->clone();
	}
	return *this;
}

Character::~Character() {
	
	std::cout << "Character's CONSTRUCTOR called" << std::endl;
	
	for (int i = 0; i < 4; i++)
		if (this->inventory[i])
			delete this->inventory[i];
}

std::string const & Character::getName() const {
	
	return this->_name;
}

void Character::equip(AMateria* m) {
	
	for (int i = 0; i < 4; i++)
	{
		if (this->inventory[i] == NULL)
		{
			this->inventory[i] = m;
			break;
		}
	}
}

void Character::unequip(int idx) {
	
	this->inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
	
	if (idx >= 0 && idx < 4 && this->inventory[idx])
		this->inventory[idx]->use(target);
}

