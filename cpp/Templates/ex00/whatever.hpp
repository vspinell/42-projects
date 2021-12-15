/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:42:03 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/13 15:14:19 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_H
#define WHATEVER_H

#include <iostream>
#include <string>

 template<typename T>
void	swap(T &a, T &b)
{
	T c;
	c = a;
	a = b;
	b = c;
}

 template<typename T>
T min(T a, T b)
{
	if (a < b)
		return a;
	return b;
}

 template<typename T>
T max(T a, T b)
{
	if (a > b)
		return a;
	return b;
}

#endif