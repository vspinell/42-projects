/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:12:40 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/26 15:42:53 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"


MateriaSource::MateriaSource() {

	std::cout << "MateriaSource's CONSTRUCTOR called" << std::endl;
	for (int i = 0; i < 4; i++)
		this->_source[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &src) {
	this->operator=(src);
}

MateriaSource&	MateriaSource::operator = (const MateriaSource &src)
{
	int i = 0;
	if (this != &src)
	{
		while (this->_source[i])
		{
			delete this->_source[i];
			i++;
		}
		for (int i = 0; i < 4; i++)
			if (src._source[i])
				this->_source[i] = src._source[i]->clone();
	}
	return *this;
}

MateriaSource::~MateriaSource() {
	
	std::cout << "MateriaSource's CONSTRUCTOR called" << std::endl;
	
	for (int i = 0; i < 4; i++)
		if (this->_source[i])
			delete this->_source[i];
}

void MateriaSource::learnMateria(AMateria* src) {
	
	for (int i = 0; i < 4; i++)
	{
		if (this->_source[i] == NULL)
		{
			this->_source[i] = src;
			break ;
		}
	}
}

AMateria* MateriaSource::createMateria(std::string const & type) {

	for (int i = 0; i < 4; i++)
	{
		if (this->_source[i] && this->_source[i]->getType() == type)
			return (this->_source[i]->clone());
	}
	return 0;
}