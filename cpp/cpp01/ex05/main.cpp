/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:24:02 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 15:24:24 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int main()
{
	Karen Karen;

	Karen.complain("debug");
	Karen.complain("error");
	Karen.complain("warning");
	Karen.complain("info");

}