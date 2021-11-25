/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:32:49 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/25 12:36:10 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice:Ice() : AMateria("ice") {
	
}

AMateria* clone() const {
	
	AMateria *tmp = new Ice(*this);
	return tmp;
}