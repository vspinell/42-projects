#ifndef SCAVTRAP_H
#define SCAVTRAP_H

#include "ClapTrap.hpp"

class ScavTrap: public ClapTrap {
	public:
		ScavTrap();
		ScavTrap(std::string name);
		~ScavTrap();
		ScavTrap(const ScavTrap &p1);
		void attack(std::string const & target);
		ScavTrap& operator = (const ScavTrap &p1);
		void guardGate();
};

#endif