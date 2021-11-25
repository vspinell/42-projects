/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:49:42 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 11:50:06 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"


int main()
{
	//Attiva il commento di sotto per vedere l'errore;
	
	// Animal prova;
	int n = 4;
	const Animal *animals[n];
	
	for (int i = 0; i < n; i++)
	{
		if (i < n / 2)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}

	for (int i = 0; i < n; i++)
		delete animals[i];

	std::cout << "\n--------------------------\n";

	Dog *a = new Dog();
	Dog *b = new Dog(*a);

	std::cout << "\n";

	a->printaddress();
	b->printaddress();
	std::cout << "\n";
	 delete a;
}