/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:24:02 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/15 11:10:06 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"


int main(int ac, char **av)
{
	if (ac == 2)
	{
		int index;
		Karen ob;
		std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
		
		for (int i = 0; i < 4; i++)
		{
			if (levels[i] == av[1])
				index = i;
		}
		switch (index)
		{
			case 0:
				ob.complain("DEBUG");
				std::cout << std::endl;
			case 1:
				ob.complain("INFO");
				std::cout << std::endl;
			case 2:
				ob.complain("WARNING");
				std::cout << std::endl;
			case 3:
				ob.complain("ERROR");
				std::cout << std::endl;
				break;
			default :
				std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
				std::cout << std::endl;
		}
	}
	return (0);
}