/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:41:09 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/18 13:18:06 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"


int main()
{
	DiamondTrap pino("Pino");
	pino.attack("Flavio");

	pino.beRepaired(23);
	pino.whoAmI();
	pino.takeDamage(22);
	// pino.beRepaired(10);
	
	// pino.attack("Ignazio");
	
	// pino.takeDamage(10);

	// pino.beRepaired(10);
	
	// pino.highFivesGuys();
}