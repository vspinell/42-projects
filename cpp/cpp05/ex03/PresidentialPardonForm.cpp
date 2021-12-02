/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:54:13 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/02 15:47:05 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string const target) : 
			AForm("PresidentialPardonForm", 25, 5), _target(target) {
	
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &src) : AForm( src ), _target(src._target) {
	
}

PresidentialPardonForm::~PresidentialPardonForm() {
	
}

void		PresidentialPardonForm::actions( void ) const
{
	std::cout << this->_target << " has been pardoned by Zafod Beeblebrox\n";

}