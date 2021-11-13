/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:29:47 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 10:06:59 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string name) : str(name) {
	
}

Weapon::~Weapon() {
	
}

void	Weapon::set_str(std::string content) {
	this->str = content;
}
const std::string& Weapon::get_str() {
	return(this->str);
}

