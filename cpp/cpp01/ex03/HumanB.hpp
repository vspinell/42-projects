/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:29:43 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 11:45:36 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_B
#define HUMAN_B

#include "Weapon.hpp"

class HumanB {
	
	std::string	_Name;
	Weapon	*_Weapon;
	public:
		HumanB(std::string name);
		~HumanB();
	void	attack() ;
	void	set_weapon(Weapon &haxPTR);
};

#endif