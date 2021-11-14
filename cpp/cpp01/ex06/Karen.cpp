/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:22:23 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 16:15:46 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

Karen::Karen() {

	this->actions[0] = &Karen::debug;
	this->actions[1] = &Karen::info;
	this->actions[2] = &Karen::warning;
	this->actions[3] = &Karen::error;
}
Karen::~Karen() {
	
}

void Karen::complain( std::string level ) {
	
	int index = -1;
	std::string levels[4] = {"debug", "info", "warning", "error"};
	
	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
			index = i;
			//(this->*(actions[i]))();
	}
	while (index < 4)
	{
		switch (index)
		{
			case 0:
				(this->*(actions[index]))();;
				std::cout << std::endl;
				break;
			case 1:
				(this->*(actions[index]))();
				std::cout << std::endl;
				break;
			case 2:
				(this->*(actions[index]))();
				std::cout << std::endl;
				break;
			case 3:
				(this->*(actions[index]))();
				std::cout << std::endl;
				break;
			default :
				std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
				exit (1);
		}
		index++;
	}
}

void Karen::debug( void ) {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I just love it!" << std::endl;
}
void Karen::info( void ) {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon cost more money. You don’t put enough! If you did I would not have to ask for it!" << std::endl;
}
void Karen::warning( void ) {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free.\nI’ve been coming here for years and you just started working here last month." << std::endl;
}
void Karen::error( void ) {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable, I want to speak to the manager now." << std::endl;
}