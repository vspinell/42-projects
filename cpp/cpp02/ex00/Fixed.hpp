/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:45:57 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/15 13:09:34 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_H
#define FIXED_H

#include <iomanip>
#include <iostream>

class Fixed {
	
	int val;
	int static const val_bits = 8;
	public:
		Fixed();
		~Fixed();
		Fixed(const Fixed &p1);
		Fixed operator=(const Fixed& b);
		int	getRawBits( void ) const;
		void setRawBits( int const raw );
};

#endif