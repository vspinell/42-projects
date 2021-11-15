/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:45:57 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/15 16:52:45 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_H
#define FIXED_H

#include <iomanip>
#include <iostream>
#include <cmath>

class Fixed {
	
	int val;
	int static const fractional_bits = 8;
	public:
		Fixed();
		Fixed(const int i);
		Fixed(const float f);
		~Fixed();
		Fixed(const Fixed &p1);
		Fixed& operator=(const Fixed& b);
		float toFloat( void ) const;
		int toInt( void ) const;
		int	getRawBits( void ) const;
		void setRawBits( int const raw );
};
std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif