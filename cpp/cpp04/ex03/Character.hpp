/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:57:45 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/28 10:10:02 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "ICharacter.hpp"

class Character : public ICharacter
{
	std::string	_name;
	AMateria	*inventory[4];
	
	public:
		Character();
		Character(std::string const & name);
		~Character();
		Character(const Character &src);

		Character& operator = (const Character &src);

		void equip(AMateria * m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);

		std::string const & getName( void ) const;
};

#endif