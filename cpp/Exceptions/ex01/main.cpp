/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:27:46 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/04 12:04:29 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <unistd.h>

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
			Form f("Pratica per la 104", n, n);
			std::cout << b << std::endl;
			std::cout << f;
			f.beSigned(b);
			if (b.getGrade() <= f.getSignGrade())
			{
				std::cout << "\e[1;34mBureaucrat is signing the form...\033[0m" << std::endl;
				sleep(2);
				std::cout << f;
			}
		
		//activate to see the error
			// b.signForm(f);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}