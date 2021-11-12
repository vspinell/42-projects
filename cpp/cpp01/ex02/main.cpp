/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:16:04 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/12 18:24:34 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
	std::string str= "HI THIS IS BRAIN";
	std::string*	stringPTR = &str;
	std::string&	stringREF = str;

	std::cout << "this is the address of the string (original): " << &str << std::endl;
	std::cout << "this is the address of the stringREF (reference): " << &stringREF << std::endl;
	std::cout << "this is the address of the stringPTR (pointer): " << &stringPTR << std::endl;
}
