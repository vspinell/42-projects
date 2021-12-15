/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:02:31 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/14 15:55:02 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main()
{
	try
	{
		int myint[] = {13, 44, 73, -1};
		std::list<int> mylist(myint, myint + sizeof(myint) / sizeof(int));
		std::cout << easyfind(mylist, 234) << std::endl;
	}
	catch(const char* e)
	{
		std::cerr << e << '\n';
	}
	try
	{
		int myint[] = {13, 44, 73, -1};
		std::list<int> mylist (myint, myint + sizeof(myint) / sizeof(int));
		std::cout << "Position Number: " << easyfind(mylist, -1) << std::endl;
	}
	catch(const char* e)
	{
		std::cerr << e << '\n';
	}
	

}