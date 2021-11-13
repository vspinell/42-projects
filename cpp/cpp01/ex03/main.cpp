/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:56:25 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 11:54:29 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
	{
		Weapon	club = Weapon("Crude spiked club");
		
		HumanA	Mario("Mario", club);
		Mario.attack();
		club.set_str("Stick");
		Mario.attack();
	}
	{
		Weapon	club = Weapon("Crude spiked club");
		HumanB	Fulloa("Fulloa");
		Fulloa.set_weapon(club);
		Fulloa.attack();
		club.set_str("Fagiolo");
		Fulloa.attack();
	}
}