/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:51:27 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/19 13:08:37 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>
#include <iomanip>

class Animal {
	protected:
		std::string type;
	public:
		Animal();
		~Animal();
		Animal(const Animal &p1);
		Animal& operator = (const Animal &p1);
		virtual void makeSound() const;
		std::string getType() const;
}; 

#endif