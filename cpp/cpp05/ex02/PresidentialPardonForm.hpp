/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:54:16 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/02 15:47:12 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_H
#define PRESIDENTIALPARDONFORM_H

#include <fstream>
#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	public:
		PresidentialPardonForm(std::string const target);
		PresidentialPardonForm(const PresidentialPardonForm &src);
		~PresidentialPardonForm();


		void		actions( void ) const;

	private:
		std::string const _target;
		PresidentialPardonForm& operator = (const PresidentialPardonForm &src);
		PresidentialPardonForm();
};

#endif