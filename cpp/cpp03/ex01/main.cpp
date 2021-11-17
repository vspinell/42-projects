/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:41:09 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/17 13:07:05 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"


int main()
{
	ScavTrap pino("Pino");
	
	pino.attack("Ignazio");
	
	pino.takeDamage(10);

	pino.beRepaired(10);
	
	pino.guardGate();
}