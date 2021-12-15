/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:00:50 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/15 15:32:21 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_H
#define MUTANTSTACK_H

#include <string>
#include <iostream>
#include <stack>

 template<typename T>
class Mutantstack : public std::stack {

	public:
		Mutantstack();
		Mutantstack(Mutantstack const &src);
		~Mutantstack();

		Mutantstack& operator = (Mutantstack const &src);
}

#endif