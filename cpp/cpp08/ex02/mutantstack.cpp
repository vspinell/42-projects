/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:07:47 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/17 15:57:56 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutantstack.hpp"

template <typename T>
MutantStack<T>::MutantStack() {
	
}

template <typename T>
MutantStack<T>::~MutantStack() {

}

template <typename T>
MutantStack<T>::MutantStack(MutantStack const &src) : std::stack<T>(src) {

	this->operator=(src);
}

template <typename T>
MutantStack<T>& MutantStack<T>::operator = (MutantStack const &src){

	this->c = src.c;
	return (*this);
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin( void )
{
	return (this->c.begin());
}

 template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end( void )
{
	return (this->c.end());
}