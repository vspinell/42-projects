/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:54:19 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/02 16:05:06 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string const target) : 
		AForm("RobotomyRequestForm", 72, 45), _target(target) {
	
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src) : AForm( src ), _target(src._target) {
	
}

RobotomyRequestForm::~RobotomyRequestForm() {
	
}

void		RobotomyRequestForm::actions( void ) const {
	
	std::cout << "driiiiiinnnnnnn" << std::endl;
	sleep(1);
	srand(time(0));
	int r = rand() % 2;

	if (r == 0)
		std::cout << this->_target << " has been robotomized successfully" << std::endl;
	else
		std::cout << this->_target << " robotomy has failed" << std::endl;
}

