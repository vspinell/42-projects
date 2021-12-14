/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:48:56 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/14 12:58:22 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>
#include <exception>

 template<typename T>
class Array {
	private:
		T *array;
		unsigned int _size;
	public:
		Array() : array(0), _size(0) {
			std::cout << "Default constractor called\n";
		}
		Array(unsigned int const len) : _size(len) {
			
			this->array = new T[len];
			for (unsigned int i = 0; i < len; i++)
				this->array[i] =  T();
		}
		~Array() {
			if (this->array)
				delete[] array;
		}
		Array& operator= (Array const &src) {
			
			std::cout << "operator = called\n";
			if (this->array)
				delete[] array;
			if (src.array != NULL && this != &src)
			{
				this->_size = src._size;
				this->array = new T[this->_size];
				for (unsigned int i = 0; i < this->_size; i++)
					this->array[i] = src.array[i];
			}
			else
			{
				this->array = NULL;
				this->_size = 0;
			}
			return *this;
		}
		Array(Array const &src) {
			
			std::cout << "copy costructor called\n";
			this->operator=(src);
		}

		unsigned int size( void ) const {
			return this->_size;
		}
		
		T const& operator [](unsigned int i) const {
			if (i >= this->_size)
				throw std::out_of_range(" this element is not accessible");
			return this->array[i];
		}
};

#endif