/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:22:39 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/13 15:42:52 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KAREN_H
# define KAREN_H

#include <iostream>
#include <string>

class Karen {

	void (Karen::*actions[4])();
	void debug( void );
	void info( void );
	void warning( void );
	void error( void );
	public:
		Karen();
		~Karen();
		void complain( std::string level );
};
#endif