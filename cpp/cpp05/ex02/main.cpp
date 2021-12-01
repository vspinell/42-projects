/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:27:46 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/01 16:24:27 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

int main()
{
	int n, x; // cambialo per vedere i diversi risultati
	while (1)
	{
		std::cout << "You decide the grade of the Bureaucrat, type it in: ";
		std::cin >> x;
		std::cout << "You decide the grade of the form, type it in: ";
		std::cin >> n;
		try
		{
			Bureaucrat b("Gulielmo", x);
			// AForm f("Pratica per la 104", n, 3);
			std::cout << b << std::endl;
			// std::cout << f;
			// f.beSigned(b);
			// std::cout << f;
		
		//activate to see the error
			// b.signForm(f);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}