/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:00:25 by vspinell          #+#    #+#             */
/*   Updated: 2021/11/26 12:52:27 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_H
#define MATERIASOURCE_H

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	AMateria * _source[4];

	public:
		MateriaSource();
		~MateriaSource();
		MateriaSource(const MateriaSource & src);

		MateriaSource& operator= (const MateriaSource & src);
		void learnMateria(AMateria* src);
		AMateria* createMateria(std::string const & type);
};

#endif