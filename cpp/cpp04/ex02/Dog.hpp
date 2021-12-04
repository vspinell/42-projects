/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:54:21 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 11:49:34 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_H
#define DOG_H

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	
	Brain* _brain;
	// std::string address;
	public:
		Dog();
		~Dog();
		Dog(const Dog &p1);
		Dog& operator = (const Dog &p1);
		// std::string getType() const;
		void		makeSound() const ;
		void		printaddress() const;
};

#endif