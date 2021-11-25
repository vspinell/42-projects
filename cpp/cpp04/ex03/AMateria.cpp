/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:17:23 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 12:22:45 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria() {
	std::cout << "AMateria's DEFAULT CONSTRUCTOR called" << std::endl;
	return ;
}

AMateria::~AMateria()
{
	std::cout << "AMateria's DEFAULT DESTRUCTOR called" << std::endl;
	return ;
}

AMateria::AMateria(std::string const & type) : _type(type) {
	
}

std::string const & AMateria::getType( void ) const {

	return this->_type;
}