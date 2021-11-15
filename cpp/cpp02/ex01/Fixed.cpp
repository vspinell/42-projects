/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:56:21 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/15 16:55:38 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() {

	std::cout << "Default constructor called" << std::endl;
	this->val = 0;
}

Fixed::Fixed(const int i) {

	std::cout << "Int constructor called" << std::endl;
	this->val = i << fractional_bits;
}

Fixed::Fixed(const float f) {

	std::cout << "Float constructor called" << std::endl;
	this->val = (int)(f * ( 1 << this->fractional_bits));
}

Fixed::~Fixed() {
	
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &p1) {

	std::cout << "Copy constructor called" << std::endl;
	this->operator=(p1);
}

void Fixed::setRawBits( int const raw ) {
	
	this->val = raw;
}

int	Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called" << std::endl;
	return val;
}

Fixed& Fixed::operator=(const Fixed& p2) {
	std::cout << "Assignation operator called" << std::endl;
	this->val = p2.val;
	return *this;

}

std::ostream& operator<<(std::ostream& os, const Fixed& obj)
{

	os << obj.toFloat();
	return os;
}

int Fixed::toInt( void ) const {
	
	return this->val >> fractional_bits;
}

float Fixed::toFloat( void ) const {
	return (float)(this->val) / (1 << fractional_bits);
}