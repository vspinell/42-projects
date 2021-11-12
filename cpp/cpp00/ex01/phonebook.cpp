/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:39:34 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/11 15:15:57 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassRubrica.hpp"

int main () {

	int index = 0;
	int len;
	Rubrica PhoneBook;
	std::string buff;
	while (buff != "EXIT")
	{
		std::cout << BWHT << std::setw(40) << "PHONEBOOK" << RESET << std::endl;
		std::cout << "Chose one action:" << std::endl;
		std::cout << std::setw(23 + 9) << "ADD (Add a new contact)" << std::endl;
		std::cout << std::setw(44 + 9) << "SEARCH (Display the contact on the phonbook)" << std::endl;
		std::cout << std::setw(27 + 9) << "Exit (to close the program)" << std::endl;
		std::cin >> buff;
		if (buff == "ADD")
		{
			PhoneBook.add_contact(index % 8);
			index++;
		}
		else if (buff == "SEARCH")
		{
			std::cout << std::setw (23) << BWHT << "CONTACT TABLE" << RESET << std::endl;
			len = index > 8 ? 8 : index;
			std::cout << " ";
			std::cout << std::setfill ('_') << std::setw (44) << " " << std::setfill (' ') << std::endl;
			for (int i = 0; i < len; i++)
				PhoneBook.print_contacts(i);
			std::cout << " ";
			std::cout << std::setfill ('-') << std::setw (44) << " " << std::setfill (' ') << std::endl;
			PhoneBook.print_selected(len);
			
		}
	}
}