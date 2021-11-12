/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:49:13 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/12 13:26:11 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_H
# define ZOMBIE_H

#include <iostream>
#include <string>


class Zombie {

	std::string _name;
	
	public:
		Zombie(std::string name);
		~Zombie();
		void	announce( void );
};

Zombie* newZombie( std::string name );
void randomChump( std::string name );

#endif