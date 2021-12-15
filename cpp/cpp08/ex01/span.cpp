/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:40:02 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/15 13:05:44 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

Span::Span() {

}

Span::Span(unsigned int const N) : _limit(N) {

	this->container.reserve(N);
}

Span::Span(Span const &src) {
	this->operator= (src);
}

Span::~Span() {
	
}


Span& Span::operator = (Span const &src) {

	this->_limit = src._limit;
	this->container = src.container;
	return *this;
}


void	Span::addNumber(const int n) {
	
	if (this->container.size() >= this->_limit)
		throw ("Error: No more space in the container");
	container.push_back(n);
}


int	Span::shortestSpan(void) {

	if (this->container.size() < 2)
		throw ("Error: too few elements in the container");
	int temp_span;
	int shortest = abs(this->container[1] - this->container[0]);
	for (unsigned long int i = 0; i < this->container.size(); i++)
	{
		for (unsigned long int y = i + 1; y < this->container.size(); y++)
		{
			temp_span = abs(this->container[y] - this->container[i]);
			if (temp_span < shortest)
				shortest = temp_span;
		}
	}
	return (shortest);
}

int	Span::longestSpan(void) {

	if (this->container.size() < 2)
		throw ("Error: too few elements in the container");
	int temp_span;
	int longest = abs(this->container[1] - this->container[0]);
	for (unsigned long int i = 0; i < this->container.size(); i++)
	{
		for (unsigned long int y = i + 1; y < this->container.size(); y++)
		{
			temp_span = abs(this->container[y] - this->container[i]);
			if (temp_span > longest)
				longest = temp_span;
		}
	}
	return (longest);
}

void Span::printvector( void ) const {

	for (unsigned long int i = 0; i < this->container.size(); i++)
		std::cout << this->container[i] << std::endl;
}