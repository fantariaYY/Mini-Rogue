#ifndef _DRAGONS_H_
#define _DRAGONS_H_

#include "Actor.h"
#include "Coord.h"

class Dungeon;

class Dragons :public Actor{
public:
	Dragons(Coord c);
	virtual ~Dragons();

	void action(Coord playerCoord, Dungeon* dungeon, std::string &outputMessage);
};

#endif