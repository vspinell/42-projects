/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:41:09 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/17 11:27:07 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"


int main()
{
	ClapTrap pino("Pino");
	
	pino.attack("Ignazio");
	
	pino.takeDamage(10);

	pino.beRepaired(10);
}