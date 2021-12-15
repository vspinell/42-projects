/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:43:12 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/15 12:41:42 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_H
#define SPAN_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>

class Span {

	unsigned int _limit;
	std::vector<int> container;

	public:
		Span();
		Span(unsigned int const N);
		~Span();
		Span(Span const &src);

		Span& operator= (Span const &src);

		void	addNumber(const int n);
		int		shortestSpan(void);
		int		longestSpan( void );
};


#endif