/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:49:13 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/12 18:03:42 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_H
# define ZOMBIE_H

#include <iostream>
#include <string>


class Zombie {

	std::string	_name;
	static int	i;

	public:
		Zombie();
		~Zombie();
		void	announce( void );
		void	set_name(std::string name);
};

Zombie* zombieHorde( int N, std::string name );

#endif