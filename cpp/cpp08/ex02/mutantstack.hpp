/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:00:50 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/17 15:42:53 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_H
#define MUTANTSTACK_H

#include <string>
#include <iostream>
#include <stack>

 template<typename T>
class MutantStack : public std::stack<T> {

	public:
		MutantStack();
		MutantStack(MutantStack const &src);
		~MutantStack();

		typedef typename std::stack<T>::container_type::iterator iterator;
		iterator begin( void );
		iterator end( void );

		MutantStack& operator = (MutantStack const &src);
};

#endif