/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassContact.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:09:10 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/11 11:29:22 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassContact.hpp"


Contact::Contact( void ) {

}
Contact::~Contact() {

}

void	Contact::set_index(int i) {

	this->index = i;

}

void	Contact::set_first_name(std::string str) {

	this->first_name = str;
}
void	Contact::set_last_name(std::string str) {

	this->last_name = str;
}
void	Contact::set_nickname(std::string str) {

	this->nickname = str;
}
void	Contact::set_number(std::string str) {

	this->phone_number = str;
}
void	Contact::set_darkest(std::string str) {

	this->darkest_secret = str;

}

int	Contact::get_index() {

	return (this->index);
}

std::string Contact::get_first_name(){
	return (this->first_name);
}
std::string Contact::get_last_name(){
	return(this->last_name);
}
std::string Contact::get_nickname() {
	return (this->nickname);
}
std::string Contact::get_number() {
	return (this->phone_number);
}
std::string Contact::get_secret() {
	return (this->darkest_secret);
}
