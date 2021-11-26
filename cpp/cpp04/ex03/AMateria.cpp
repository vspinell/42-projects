/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:17:23 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/26 10:43:22 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria() {
	std::cout << "AMateria's DEFAULT CONSTRUCTOR called" << std::endl;
	return ;
}

AMateria::AMateria(const AMateria &src) {
	this->_type = src.getType();
}

AMateria::~AMateria()
{
	std::cout << "AMateria's DEFAULT DESTRUCTOR called" << std::endl;
	return ;
}

AMateria::AMateria(std::string const & src) : _type(src) {
	
}

AMateria& AMateria::operator=(const AMateria &src){
	if (this != &src)
	{
		this->_type = src.getType();
	}
	return *this;
}

std::string const & AMateria::getType( void ) const {

	return this->_type;
}

void AMateria::use(ICharacter& target) {
	
	std::cout << this->_type << " does something to " << target.getName() << std::endl;

}