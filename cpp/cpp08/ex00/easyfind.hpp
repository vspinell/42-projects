/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:20:21 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/17 16:34:25 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_H
#define EASYFIND_H

#include <iostream>
#include <string>
#include <vector>

 template <typename T>
typename T::iterator	easyfind(T t, int ser)
{
	
	typename T::iterator it;
	it = std::find(t.begin(), t.end(), ser);
	if (it != t.end())
		return it;
	throw ("Cannot be found");
}

#endif