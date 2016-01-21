#ifndef _SNAKEWOMEN_H_
#define _SNAMEWOMEN_H_

#include "Actor.h"
#include "Coord.h"

class Dungeon;

class Snakewomen :public Actor{
public:
	Snakewomen(Coord c);
	virtual ~Snakewomen();

	void action(Coord playerCoord, Dungeon* dungeon, std::string &outputMessage);
};

#endif