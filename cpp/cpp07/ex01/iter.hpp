/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:24:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/13 16:41:03 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_H
#define ITER_H

#include <string>
#include <iostream>

 template<typename T>
void print(T toprint)
{
	std::cout << toprint << std::endl;
}

 template<typename T>
void	iter(T * addr, int len, void (*print)(T a))
{
	for (int i = 0; i < len; i++)
		print(addr[i]);
}


#endif