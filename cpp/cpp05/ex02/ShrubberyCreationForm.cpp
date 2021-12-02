/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:54:24 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/02 15:29:41 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string const target) : 
			AForm("ShrubberyCreationForm", 145, 137), _target(target) {
	
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src) : AForm( src ), _target(src._target) {
	
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	
}


void		ShrubberyCreationForm::actions( void ) const
{
	std::string const three[1] =
	{
		"             * *    \n" \
		"           *    *  *\n" \
		"      *  *    *     *  *\n" \
		"     *     *    *  *    *\n" \
		" * *   *    *    *    *   *\n" \
		" *     *  *    * * .#  *   *\n" \
		" *   *     * #.  .# *   *\n" \
		"  *     \"#.  #: #\" * *    *\n" \
		" *   * * \"#. ##\"       *\n" \
		"   *       \"###\n" \
		"             \"##\n" \
		"              ##.\n" \
		"              .##:\n" \
		"              :###\n" \
		"              ;###\n" \
		"            ,####.\n" \
		"/\\/\\/\\/\\/\\/.######.\\/\\/\\/\\/\n" 
	};
	std::string pathfile = this->_target + "_shrubbery";
	std::ofstream newfile (pathfile.c_str(), std::ios::trunc);
	newfile << three[0];
	newfile.close();
}