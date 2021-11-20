/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:15:20 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/20 19:13:02 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain() {

	std::cout << "Brain exist" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "Cibo";
}

Brain::~Brain() {

	std::cout << "Brain deleted" << std::endl;
}

Brain::Brain(const Brain &p1) {

	this->operator=(p1);
}

Brain& Brain::operator= (const Brain &p1) {
	
	std::cout << "Overload = Brain" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = p1.ideas[i];
	return *this;
}
