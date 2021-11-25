/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:22:15 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 16:50:12 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_H
#define CURE_H

#include "AMateria.hpp";

class Cure : public AMateria {
	
	public:
		Cure();
		Cure(const Cure &src);
		~Cure();

		Cure& operator = (const Cure &src);
		AMateria* clone() const;
		void use(ICharacter& target);
};

#endif