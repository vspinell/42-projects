/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:29:50 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 10:06:33 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

#include <string>
#include <iostream>

class Weapon {

	std::string	str;

public:
	Weapon(std::string name);
	~Weapon();
	const std::string& get_str() ;
	void	set_str(std::string content);
	
};

#endif
