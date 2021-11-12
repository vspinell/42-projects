/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:09:44 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/12 13:33:56 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main ()
{
	Zombie z1("Mariello");
	Zombie z2("Agostino");
	Zombie *z3;

	z1.announce();
	z2.announce();
	z3 = newZombie("Attila");
	z3->announce();
	randomChump("Pietropaolo");
	delete (z3);
}