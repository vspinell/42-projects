/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:09:01 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 15:28:59 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>


int main(int ac, char **av)
{
	if (ac == 4)
	{
		std::string pathfile = av[1];
		std::string s1 = av[2];
		std::string s2 = av[3];
		std::size_t pos;

		std::string line;
		std::string buff;
		std::ifstream myfile (pathfile);
		std::ofstream newfile (pathfile + ".replace", std::ios::trunc);
		if (myfile.is_open())
		{
			while (std::getline (myfile, line))
			{
				buff += line;
				if (!myfile.eof())
					buff += "\n";
			}
			pos = buff.find(s1);
			if (pos != std::string::npos)
			{
				while (pos != std::string::npos)
				{
					buff.erase(pos, s1.length());
					buff.insert(pos, s2);
					pos = buff.find(s1, pos + s2.size());
				}
			}
			else
				std::cout << "File doesn't changed" << std::endl;
			newfile << buff;
		}
		else
			std::cout << "Unable to open file";
	}
	else
		std::cout << "error: wrong number of arguments" << std::endl;
	return (0);
}