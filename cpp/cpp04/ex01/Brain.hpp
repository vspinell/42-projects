/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:33:26 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/20 19:18:41 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_H
#define BRAIN_H

#include <string>
#include <iostream>

class Brain {
	
	std::string ideas[100];
	public:
		Brain();
		~Brain();
		Brain(const Brain &p1);
		Brain& operator = (const Brain &p1);
};

#endif