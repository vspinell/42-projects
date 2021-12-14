/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:48:52 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/14 13:06:04 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main()
{
	int n = 4;
	Array <std::string> standarr;
	std::cout << "size = " << standarr.size() << std::endl;
	
	Array <int> arr(n);
	std::cout << "int array len: " << arr.size() << std::endl;
	for (int i = 0; i < n - 1; i++)
		std::cout << arr[i] << ", ";
	std::cout << arr[n - 1] << "\n";

	std:: cout << "I create a new Array of int of size n + 2\n";
	Array <int> arr2(n + 2);
	std:: cout << "accessing the value of the array's last position: " << arr2[n + 1] << std::endl;
	arr2 = arr;
	std:: cout << "I try to access the original last position which now doesn't exist anymore\n\n";
	arr2[n + 1];

}