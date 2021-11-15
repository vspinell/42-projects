/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:36:56 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/15 19:37:17 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef FIXED_H
# define FIXED_H

#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>

class Fixed
{
	int _raw;
	static const int _fract_bit = 8;

	public:

	Fixed();
	Fixed(const int n);
	Fixed(const float f);
	~Fixed();
	Fixed(const Fixed &obj);
	void	operator = (const Fixed &obj);
	bool	operator == (const Fixed &obj) const;
	bool	operator != (const Fixed &obj) const;
	bool	operator > (const Fixed &obj) const;
	bool	operator >= (const Fixed &obj) const;
	bool	operator < (const Fixed &obj) const;
	bool	operator <= (const Fixed &obj) const;
	Fixed	operator + (const Fixed &obj) const;
	Fixed	operator - (const Fixed &obj) const;
	Fixed	operator * (const Fixed &obj) const;
	Fixed	operator / (const Fixed &obj) const;
	Fixed	operator ++();
	Fixed	operator ++(int);
	Fixed	operator --();
	Fixed	operator --(int);
	static Fixed &min(Fixed &obj1, Fixed &obj2);
	static const Fixed &min(const Fixed &obj1, const Fixed &obj2);
	static Fixed &max(Fixed &obj1, Fixed &obj2);
	static const Fixed &max(const Fixed &obj1, const Fixed &obj2);
	int     getRawBits() const;
	void    setRawBits(int const raw);
	int     toInt() const;
	float   toFloat() const;

};

std::ostream &operator <<(std::ostream &output, const Fixed &obj);


#endif