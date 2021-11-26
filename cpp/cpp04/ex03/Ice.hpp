/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:23:50 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/26 10:17:36 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_H
#define ICE_H

#include "AMateria.hpp"


class Ice : public AMateria {
	
	public:
		Ice();
		Ice(const Ice &src);
		~Ice();

		Ice& operator = (const Ice &src);

		AMateria* clone() const;
		void use(ICharacter& target);
};

#endif