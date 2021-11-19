/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:28:04 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/19 12:42:42 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_H
#define CAT_H

#include "Animal.hpp"

class Cat : public Animal {
	public:
		Cat();
		~Cat();
		Cat(const Cat &p1);
		Cat& operator = (const Cat &p1);
		void		makeSound() const;
};

#endif