/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:39:34 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/13 11:41:14 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <limits>


void	caseChar(std::string const str)
{
	char const c = static_cast<char const>(str[0]);
	std::cout << "Char: " << c << std::endl;
	std::cout << "Int: " << static_cast<int const>(c) << std::endl;
	std::cout << "Float: " << static_cast<float const>(c) << ".0f" << std::endl;
	std::cout << "Double: " << static_cast<double const>(c) << ".0" << std::endl;
}

void	caseInt(std::string const str)
{
	try
	{
		const long long int x = static_cast<const long long int>(atoll(str.c_str()));
		if (x > std::numeric_limits<int>::max() || x < std::numeric_limits<int>::min())
			throw (x);
		const int i = static_cast<const int>(x);
		if ((i % 256 >= 0 && i % 256 < 32) || (i % 127 == 0))
			std::cout << "Char: not displaiable\n";
		else if ((i % 256 >= 127 && i % 256 < 288) || i < 0)
			std::cout << "Char: impossible\n";
		else
			std::cout << "Char: " << static_cast<char const>(i) << std::endl;
		std::cout << "Int: " << i << std::endl;
		std::cout << "Float: " << static_cast<float const>(i) << ".0f" << std::endl;
		std::cout << "Double: " << static_cast<double const>(i) << ".0" << std::endl;
	}
	catch(long long int& e)
	{
		std::cout << e << ": out of range.";
	}
	
}

void	caseFloat(std::string const str)
{
	const float dou = static_cast<const float>(atof(str.c_str()));
	const int d = static_cast<const int>(dou);
	if ((d >= 0 && d < 32) || (d == 127))
		std::cout << "Char: not displaiable\n";
	else if ((d >= 127) || d < 0)
		std::cout << "Char: impossible\n";
	else
		std::cout << "Char: " << static_cast<char const>(d) << std::endl;
	if (dou > std::numeric_limits<int>::max() || dou <= std::numeric_limits<int>::min())
		std::cout << "Int: impossible\n";
	else
		std::cout << "Int: " << d << std::endl;
	if (static_cast<const float>(dou) - d == 0)
		std::cout << "Float: " << dou << ".0f\n";
	else
		std::cout << "Float: " << dou << "f\n";
	if (dou - static_cast<long long int const>(dou) == 0)
		std::cout << "Double: " << dou << ".0\n";
	else
		std::cout << "Double: " << dou << "\n";
}

void	caseDouble(std::string str)
{
	const double dou = static_cast<const double>(atof(str.c_str()));
	const long long int d = static_cast<const long long int>(dou);
	if ((d >= 0 && d < 32) || (d == 127))
		std::cout << "Char: not displaiable\n";
	else if ((d >= 127) || d < 0)
		std::cout << "Char: impossible\n";
	else
		std::cout << "Char: " << static_cast<char const>(d) << std::endl;
	if (dou > std::numeric_limits<int>::max() || dou <= std::numeric_limits<int>::min())
		std::cout << "Int: impossible\n";
	else
		std::cout << "Int: " << static_cast<const int>(d) << std::endl;
	
	if (dou - d == 0)
		std::cout << "Float: " << static_cast<float const>(dou) << ".0f\n";
	else
		std::cout << "Float: " <<  static_cast<float const>(dou) << "f\n";
	if (dou - static_cast<long long int const>(dou) == 0)
		std::cout << "Double: " << dou << ".0\n";
	else
		std::cout << "Double: " << dou << "\n";


}

int	detectType(std::string str)
{
	if (str.size() == 1 && (str[0] < 48 || str[0] > 57))
		return (1);
	if (str.find(".") == std::string::npos && str.find("n") == std::string::npos)
		return (2);
	if (str[str.size() - 1] == 'f' && str != "+inf" && str != "-inf")
		return (3);
	else
		return (4);
}


int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: invalid number of arguments\n";
		return (1);
	}
	std::string const str = static_cast<std::string const>(av[1]);
	int PickCase = detectType(str);
	switch (PickCase)
	{
		case 1: caseChar(str);		break;
		case 2: caseInt(str);		break;
		case 3: caseFloat(str);		break;
		case 4: caseDouble(str);	break;

		default:
			break;
	}
}