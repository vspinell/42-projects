/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:51:27 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 11:57:15 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_H
#define AANIMAL_H

#include <iostream>
#include <string>
#include <iomanip>

class Animal {
	protected:
		std::string type;
	public:
		Animal();
		virtual ~Animal();
		Animal(const Animal &p1);
		Animal& operator = (const Animal &p1);
		virtual void makeSound() const = 0;
		std::string getType() const;
		virtual void	printaddress() const {};
}; 

#endif