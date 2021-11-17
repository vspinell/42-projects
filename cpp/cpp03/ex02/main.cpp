/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:41:09 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/17 13:56:43 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "FragTrap.hpp"


int main()
{
	FragTrap pino("Pino");
	
	pino.attack("Ignazio");
	
	pino.takeDamage(10);

	pino.beRepaired(10);
	
	pino.guardGate();
}