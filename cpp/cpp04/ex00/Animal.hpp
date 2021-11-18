/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:51:27 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/18 17:32:25 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_H
#define ANIMAL

#include <iostream>
#include <string>

class Animal {
	protected:
		std::string type;
	public:
		Animal();
		~Animal();
		Animal(const Animal &p1);
		Animal& operator = (const Animal &p1);
		void makeSound();
		std::string getType() const;
};

#endif