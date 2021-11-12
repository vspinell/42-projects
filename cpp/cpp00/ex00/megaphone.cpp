/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:53:18 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/10 16:43:18 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int main(int argc, char **argv) {

	char *buff;

	if (argc != 1)
	{
		for (int i = 1; i < argc; i++)
		{
			buff = argv[i];
			for (int y = 0; buff[y]; y++)
				std::cout << (char)toupper(buff[y]);
		}
		std::cout << std::endl;
	}
	else
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
}