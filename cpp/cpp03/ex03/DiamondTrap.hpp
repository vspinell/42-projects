/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:02:00 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/17 17:36:48 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_H
#define DIAMONDTRAP_H


#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {

	std::string _name;

	public:
		DiamondTrap();
		DiamondTrap(std::string name);
		DiamondTrap& operator = (const DiamondTrap &p1);
		DiamondTrap(const DiamondTrap &p1);
		void attack(std::string const & target);
		~DiamondTrap();
		
		void whoAmI();
};

#endif