/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:29:38 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 10:46:27 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_A
#define HUMAN_A

#include "Weapon.hpp"

class HumanA {

	std::string	_Name;
	Weapon &_Weapon;
	public:
		HumanA(std::string name, Weapon &club);
		~HumanA();
	void	attack();
};

#endif