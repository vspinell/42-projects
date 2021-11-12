/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassContact.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:09:07 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/11 11:53:16 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSCONTACT_H
# define CLASSCONTACT_H

#include <string>
#include <iostream>
#include <iomanip>

class Contact {

int			index;
std::string first_name;
std::string last_name;
std::string nickname;
std::string darkest_secret;
std::string phone_number;

public:

	int			get_index();
	Contact( void );
	~Contact ( void );
	void		set_index(int i);
	void		set_first_name(std::string str);
	void		set_last_name(std::string str);
	void		set_nickname(std::string str);
	void		set_darkest(std::string str);
	void		set_number(std::string str);
	std::string	get_first_name();
	std::string	get_last_name();
	std::string	get_nickname();
	std::string	get_number();
	std::string	get_secret();
};

#endif