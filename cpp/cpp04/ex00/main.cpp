/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:49:42 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/19 13:16:29 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"


int main()
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	std::cout << std::setfill('-') << std::setw(47) << " " << std::endl;

	const WrongAnimal* meta2 = new WrongAnimal();
	const WrongAnimal* x = new WrongCat();

	std::cout << i->getType() << " " << std::endl;
	x->makeSound(); //will output the Wrongcat sound!
	meta2->makeSound();
}