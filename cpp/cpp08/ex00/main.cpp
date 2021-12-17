/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:02:31 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/17 16:44:35 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main()
{
	try
	{
		int myint[] = {13, 44, 73, -1};
		std::vector<int> mylist(myint, myint + sizeof(myint) / sizeof(int));
		std::cout << *easyfind(mylist, 234) << std::endl;
	}
	catch(const char* e)
	{
		std::cerr << e << '\n';
	}
	try
	{


		int myint[] = {13, 44, 73, -1};
		std::vector<int> mylist (myint, myint + sizeof(myint) / sizeof(int));
		std::vector<int>::iterator it = easyfind(mylist, 13);
		std::cout << "Element " << *it <<" found at position : " ;
		std::cout << it - mylist.begin() - 4 << " (counting from zero) \n";
	}
	catch(const char* e)
	{
		std::cerr << e << '\n';
	}
	

}