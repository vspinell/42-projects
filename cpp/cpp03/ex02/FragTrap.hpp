#ifndef FRAGTRAP_H
#define FRAGTRAP_H

#include "ClapTrap.hpp"

class FragTrap: public ClapTrap {
	public:
		FragTrap();
		FragTrap(std::string name);
		~FragTrap();
		FragTrap(const FragTrap &p1);
		void attack(std::string const & target);
		FragTrap& operator = (const FragTrap &p1);
		void highFivesGuys(void);
};

#endif