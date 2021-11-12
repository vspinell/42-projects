/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassRubrica.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:31:31 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/11 15:12:32 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSRUBRICA_H
# define CLASSRUBRICA_H

#include "ClassContact.hpp"
#define BOLDGREEN	"\033[1m\033[32m"
#define RESET		"\033[0m"
#define BBLU 		"\e[1;34m"
#define GPIPE		"\e[1;33m|\033[0m"
#define BWHT		"\e[1;37m"

class Rubrica {

Contact contact[8];

public:
	
	Rubrica( void);
	~Rubrica ( void );
	void	add_contact(int index);
	void	print_contacts(int i);
	void	print_selected(int &len);
};

#endif