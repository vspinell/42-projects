/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassRubrica.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:31:05 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/11 15:14:02 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassRubrica.hpp"

Rubrica::Rubrica(void) {

}
Rubrica::~Rubrica( void ) {

}

void	Rubrica::add_contact(int index) {

	std::string name;

	std::cout << BOLDGREEN << "ADD A NEW CONTACT" << RESET << std::endl;
	this->contact[index].set_index(index + 1);
	std::cout << "Insert the FIRST NAME: ";
	std::getline (std::cin, name);
	std::getline (std::cin, name);
	this->contact[index].set_first_name(name);
	std::cout << "Insert the LAST NAME: ";
	std::getline (std::cin, name);
	this->contact[index].set_last_name(name);
	std::cout << "Insert the NICKNAME: ";
	std::getline (std::cin, name);
	this->contact[index].set_nickname(name);
	std::cout << "Insert the PHONE NUMBER: ";
	std::getline (std::cin, name);
	this->contact[index].set_number(name);
	std::cout << "Insert the DARKEST SECRET: ";
	std::getline (std::cin, name);
	this->contact[index].set_darkest(name);
}

void Rubrica::print_contacts(int i) {

	std::string str;

	std::cout << "|";
	std::cout << std::setw(10) << this->contact[i].get_index() << "|";
	for (int y = 0; y < 3; y++)
	{
		if (y == 0)
			str = this->contact[i].get_first_name();
		else if (y == 1)
			str = this->contact[i].get_last_name();
		else
			str = this->contact[i].get_nickname();
		str = (str.size() > 10) ? str.substr(0, 9) + "." : str;
		std::cout << std::setw(10) << str << "|";
	}
	std::cout << std::endl;
}

void	Rubrica::print_selected(int &len) {

	int	buff;
	std::string str;
	
	std::cin >> buff;
	if (buff > 0 && buff - 1 < len)
	{
		std::cout << BBLU << "CONTACT INFORMATIONS" << RESET << std::endl;
		std::cout <<  GPIPE"Index Number: ";
		std::cout << std::setw(3) << this->contact[buff - 1].get_index() << std::endl;
		
		str = this->contact[buff - 1].get_first_name();
		std::cout  << GPIPE"Name: ";
		std::cout << std::setw(10 + str.length())<< str << std::endl;
		
		str = this->contact[buff - 1].get_last_name();
		std::cout << GPIPE"Surname: ";
		std::cout << std::setw(7 + str.length())<< str <<  std::endl;

		str = this->contact[buff - 1].get_nickname();
		std::cout  << GPIPE"Nickname: ";
		std::cout << std::setw(6 + str.length())<< str <<  std::endl;

		str = this->contact[buff - 1].get_number();
		std::cout  << GPIPE"Phone number: ";
		std::cout << std::setw(2 + str.length())<< str <<  std::endl;
		std::cout << GPIPE"Darkest secret: "<< this->contact[buff - 1].get_secret() << std::endl;
	}
	std::cin.clear();
}
