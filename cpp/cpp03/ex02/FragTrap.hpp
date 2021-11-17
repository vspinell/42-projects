#ifndef FRAGTRAP_H
#define FRAGTRAP_H

#include "ClapTrap.hpp"

class FragTrap: public ClapTrap {
	public:
		FragTrap(std::string name);
		~FragTrap();
		FragTrap(const FragTrap &p1);
		FragTrap& operator = (const FragTrap &p1);
		void guardGate();
};

#endif