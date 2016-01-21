#ifndef _BOGEYMEN_H_
#define _BOGEYMEN_H_

#include "Actor.h"
#include "Coord.h"

class Dungeon;

class Bogeymen :public Actor{
public:
	Bogeymen(Coord c);
	virtual ~Bogeymen();

	void action(Coord playerCoord, Dungeon* dungeon, std::string &outputMessage);
};

#endif