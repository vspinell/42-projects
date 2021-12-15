/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:20:21 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/14 15:47:52 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_H
#define EASYFIND_H

#include <iostream>
#include <string>
#include <list>

 template <typename T>
int	 easyfind(T t, int value)
{
	int pos = -1;
	for (typename T::iterator it = t.begin(); it != t.end(); it++)
	{
		++pos;
		if (*it == value)
			return (pos);
	}
	throw ("Cannot be found");
}

#endif